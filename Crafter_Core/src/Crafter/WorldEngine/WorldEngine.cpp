//
// Created by Matthew Good on 14/6/21.
//

#include <type_traits>
#include <Crafter/WorldEngine/WINAPI_KERNEL/SDK/include/Windows/Kernel/WindowsAPIKernel.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Primitives/Axis.h>
#include <Magnum/Primitives/Crosshair.h>
#include <Magnum/Primitives/Grid.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Trade/MeshData.h>
#include "WorldEngine.h"

class DrawableObject: public Crafter::Rotation, public Crafter::Translation {
public:

    Magnum::GL::Mesh mesh;
    Magnum::Shaders::FlatGL3D shader{Magnum::Shaders::FlatGL3D::Flag::VertexColor};
    DrawableObject() = default;

    /** @brief Copying is not allowed */
    DrawableObject(const DrawableObject&) = delete;

    /** @brief Copying is not allowed */
    DrawableObject& operator=(const DrawableObject&) = delete;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-use-after-move"
    /** @brief Move constructor */
    DrawableObject(DrawableObject&& other) noexcept: Rotation(std::move(other)), Translation(std::move(other)) {
        using std::swap;
        swap(mesh, other.mesh);
        swap(shader, other.shader);
    }

    /** @brief Move assignment */
    DrawableObject& operator=(DrawableObject&& other) noexcept {
        Rotation::operator=(std::move(other));
        Translation::operator=(std::move(other));
        using std::swap;
        swap(mesh, other.mesh);
        swap(shader, other.shader);
        return *this;
    }
#pragma clang diagnostic pop

    Magnum::Matrix4
    projection_Type_OBJECT_TRANSLATION_IS_RELATIVE_TO_CAMERA (
            Crafter::Camera * mainCamera
    ) {
        return
        mainCamera->perspectiveProjection()
        * translationDistance(
            mainCamera->translation(),
            translation()
        )
        * mainCamera->rotation()
        * rotation()
        ;
    }

    Magnum::Matrix4
    projection_Type_OBJECT_TRANSLATION_IS_STATIC (
            Crafter::Camera * mainCamera
    ) {
        return
        mainCamera->perspectiveProjection()
        * mainCamera->translation()
        * mainCamera->rotation()
        * translation()
        * rotation()
        ;
    }

    virtual void updateMesh() {};
    virtual void draw(Crafter::Camera * mainCamera) {};
};

class Triangle_Primitive : public DrawableObject {
public:
    Triangle_Primitive() = default;
    struct TriangleVertex {
        Magnum::Vector3 position;
        Magnum::Color3 color;
    };

    TriangleVertex data[3];

    void init(const Magnum::Vector3 & left, const Magnum::Vector3 & right, const Magnum::Vector3 & top, const Magnum::Color3 color) {
        data[0] = {left, color};
        data[1] = {right, color};
        data[2] = {top, color};
        updateMesh();
    }

    void updateMesh() override {
        Magnum::GL::Buffer buffer;
        buffer.setData(data, Magnum::GL::BufferUsage::StaticDraw);
        mesh.setCount(3).addVertexBuffer(std::move(buffer), 0, Magnum::Shaders::FlatGL3D::Position{}, Magnum::Shaders::FlatGL3D::Color3{});
    }

    void draw(Crafter::Camera * mainCamera) override {
        shader
                .setTransformationProjectionMatrix(
                        projection_Type_OBJECT_TRANSLATION_IS_STATIC(mainCamera)
                ).draw(mesh);
    }
};

class DrawableObjectGroup : public Crafter::Rotation, public Crafter::Translation {
    Kernel kernel;
    class KEY {
    public:
        const char * key;
        AnyOpt drawableObject;
        AnyOpt drawableObjectGroup;

        KEY(const char * key, AnyOpt drawableObject, AnyOpt drawableObjectGroup) {
            this->key = key;
            this->drawableObject = drawableObject;
            this->drawableObjectGroup = drawableObjectGroup;
        }
    };

public:
    Object * find_key(const char * key, size_t resource_len) {
        int page = 1;
        size_t index = 0;
        size_t page_size = kernel.table->page_size;
        for (; page <= kernel.table->Page.count(); page++) {
            index = ((page_size * page) - page_size);
            for (; index < page_size * page; index++)
                if (kernel.table->table[index] != nullptr) {
                    Object * object = kernel.table->table[index];
                    KEY * key_ = object->resource.get<KEY *>();
                    const char *data = key_->key;
                    if (!memcmp(data, key, resource_len))
                        return object;
                    if (key_->drawableObjectGroup.has_value()) {
                        Object *object1 = key_->drawableObjectGroup.get<DrawableObjectGroup *>()
                                ->find_key(key, resource_len);
                        // don't return if key cannot be found in child object group
                        if (object1 != nullptr) return object1;
                    }
                }
        }
        return nullptr;
    }

    Object * find_key(const char * key) {
        return find_key(key, strlen(key));
    }

    template <typename T> T * createDrawableObject() {
        static_assert(std::is_convertible<T, DrawableObject>::value, "T must extend DrawableObject: change 'class T { /* ... */ }' to 'class T: public DrawableObject { /* ... */ }'");
        Object * o = kernel
                .newObject(ObjectTypeNone, ObjectFlagNone, KEY{nullptr, T(), AnyNullOpt});
        return o == nullptr ? nullptr : o->resource.get<KEY*>()->drawableObject.get<T*>();
    }

    template <typename T> T * createDrawableObject(const char * key) {
        static_assert(std::is_convertible<T, DrawableObject>::value, "T must extend DrawableObject: change 'class T { /* ... */ }' to 'class T: public DrawableObject { /* ... */ }'");
        Object * o = kernel
                .newObject(ObjectTypeNone, ObjectFlagNone, KEY{key, T(), AnyNullOpt});
        return o == nullptr ? nullptr : o->resource.get<KEY*>()->drawableObject.get<T*>();
    }

    template <typename T> T * getDrawableObject(const char * key) {
        static_assert(std::is_convertible<T, DrawableObject>::value, "T must extend DrawableObject: change 'class T { /* ... */ }' to 'class T: public DrawableObject { /* ... */ }'");
        Object * o = find_key(key);
        if (o == nullptr) return nullptr;
        return o->resource.get<KEY *>()->drawableObject.get<T*>();
    }

    void AddDrawableObjectGroup(const char * key, DrawableObjectGroup * drawableObjectGroup) {
        kernel.newObject(ObjectTypeNone, ObjectFlagNone, KEY{key, AnyNullOpt, drawableObjectGroup});
    }

    DrawableObjectGroup * getDrawableObjectGroup(const char * key) {
        Object * o = find_key(key);
        if (o == nullptr) return nullptr;
        return o->resource.get<KEY *>()->drawableObjectGroup.get<DrawableObjectGroup*>();
    }

#define ACTION(DrawableObject_PTR, CODE) { \
    int page = 1; \
    size_t index; \
    size_t page_size = kernel.table->page_size; \
    for (; page <= kernel.table->Page.count(); page++) { \
        index = ((page_size * page) - page_size); \
        for (; index < page_size * page; index++) \
            if (kernel.table->table[index] != nullptr) { \
                Object * object = kernel.table->table[index]; \
                KEY * key_ = object->resource.get<KEY *>(); \
                if (key_->drawableObject.has_value()) {  \
                    DrawableObject * DrawableObject_PTR = key_->drawableObject.get<DrawableObject*>(); \
                    CODE \
                } \
            } \
    } \
}\


    virtual void draw(Crafter::Camera * mainCamera) const {
        ACTION(x, x->draw(mainCamera);)
    }

    void setRotationX(const float &degrees) override {
        Rotation::setRotationX(degrees);
        ACTION(x, x->subRotationX(r_x); x->addRotationX(degrees); )
    }

    void addRotationX(const float &degrees) override {
        Rotation::addRotationX(degrees);
        ACTION(x, x->addRotationX(degrees);)
    }

    void subRotationX(const float &degrees) override {
        Rotation::subRotationX(degrees);
        ACTION(x, x->subRotationX(degrees);)
    }

    void mulRotationX(const float &degrees) override {
        Rotation::mulRotationX(degrees);
        ACTION(x, x->mulRotationX(degrees);)
    }

    void divRotationX(const float &degrees) override {
        Rotation::divRotationX(degrees);
        ACTION(x, x->divRotationX(degrees);)
    }

    Magnum::Matrix4 rotationX() override {
        return Rotation::rotationX();
    }

    void setRotationY(const float &degrees) override {
        Rotation::setRotationY(degrees);
        ACTION(x, x->subRotationY(r_y); x->addRotationY(degrees); )
    }

    void addRotationY(const float &degrees) override {
        Rotation::addRotationY(degrees);
        ACTION(x, x->addRotationY(degrees);)
    }

    void subRotationY(const float &degrees) override {
        Rotation::subRotationY(degrees);
        ACTION(x, x->subRotationY(degrees);)
    }

    void mulRotationY(const float &degrees) override {
        Rotation::mulRotationY(degrees);
        ACTION(x, x->mulRotationY(degrees);)
    }

    void divRotationY(const float &degrees) override {
        Rotation::divRotationY(degrees);
        ACTION(x, x->divRotationY(degrees);)
    }

    Magnum::Matrix4 rotationY() override {
        return Rotation::rotationY();
    }

    void setRotationZ(const float &degrees) override {
        Rotation::setRotationX(degrees);
        ACTION(x, x->subRotationZ(r_z); x->addRotationZ(degrees); )
    }

    void addRotationZ(const float &degrees) override {
        Rotation::addRotationZ(degrees);
        ACTION(x, x->addRotationZ(degrees);)
    }

    void subRotationZ(const float &degrees) override {
        Rotation::subRotationZ(degrees);
        ACTION(x, x->setRotationZ(degrees);)
    }

    void mulRotationZ(const float &degrees) override {
        Rotation::mulRotationZ(degrees);
        ACTION(x, x->mulRotationZ(degrees);)
    }

    void divRotationZ(const float &degrees) override {
        Rotation::divRotationZ(degrees);
        ACTION(x, x->divRotationZ(degrees);)
    }

    Magnum::Matrix4 rotationZ() override {
        return Rotation::rotationZ();
    }

    void setRotation(const float &x, const float &y, const float &z) override {
        Rotation::setRotation(x, y, z);
        ACTION(x_, x_->subRotation(r_x, r_y, r_z); x_->addRotation(x, y, z); )
    }

    void addRotation(const float &x, const float &y, const float &z) override {
        Rotation::addRotation(x, y, z);
        ACTION(x_, x_->addRotation(x, y, z);)
    }

    void subRotation(const float &x, const float &y, const float &z) override {
        Rotation::subRotation(x, y, z);
        ACTION(x_, x_->subRotation(x, y, z);)
    }

    void mulRotation(const float &x, const float &y, const float &z) override {
        Rotation::mulRotation(x, y, z);
        ACTION(x_, x_->mulRotation(x, y, z);)
    }

    void divRotation(const float &x, const float &y, const float &z) override {
        Rotation::divRotation(x, y, z);
        ACTION(x_, x_->divRotation(x, y, z);)
    }

    Magnum::Matrix4 rotation() override {
        return Rotation::rotation();
    }

    void setTranslationX(const float &translation) override {
        Translation::setTranslationX(translation);
        ACTION(x, x->subTranslationX(r_x); x->addTranslationX(translation); )
    }

    void addTranslationX(const float &translation) override {
        Translation::addTranslationX(translation);
        ACTION(x, x->addTranslationX(translation);)
    }

    void subTranslationX(const float &translation) override {
        Translation::subTranslationX(translation);
        ACTION(x, x->subTranslationX(translation);)
    }

    void mulTranslationX(const float &translation) override {
        Translation::mulTranslationX(translation);
        ACTION(x, x->mulTranslationX(translation);)
    }

    void divTranslationX(const float &translation) override {
        Translation::divTranslationX(translation);
        ACTION(x, x->divTranslationX(translation);)
    }

    Magnum::Matrix4 translationX() override {
        return Translation::translationX();
    }

    void setTranslationY(const float &translation) override {
        Translation::setTranslationY(translation);
        ACTION(x, x->subTranslationY(r_y); x->addTranslationY(translation); )
    }

    void addTranslationY(const float &translation) override {
        Translation::addTranslationY(translation);
        ACTION(x, x->addTranslationY(translation);)
    }

    void subTranslationY(const float &translation) override {
        Translation::subTranslationY(translation);
        ACTION(x, x->subTranslationY(translation);)
    }

    void mulTranslationY(const float &translation) override {
        Translation::mulTranslationY(translation);
        ACTION(x, x->mulTranslationY(translation);)
    }

    void divTranslationY(const float &translation) override {
        Translation::divTranslationY(translation);
        ACTION(x, x->divTranslationY(translation);)
    }

    Magnum::Matrix4 translationY() override {
        return Translation::translationY();
    }

    void setTranslationZ(const float &translation) override {
        Translation::setTranslationX(translation);
        ACTION(x, x->subTranslationZ(r_z); x->addTranslationZ(translation); )
    }

    void addTranslationZ(const float &translation) override {
        Translation::addTranslationZ(translation);
        ACTION(x, x->addTranslationZ(translation);)
    }

    void subTranslationZ(const float &translation) override {
        Translation::subTranslationZ(translation);
        ACTION(x, x->setTranslationZ(translation);)
    }

    void mulTranslationZ(const float &translation) override {
        Translation::mulTranslationZ(translation);
        ACTION(x, x->mulTranslationZ(translation);)
    }

    void divTranslationZ(const float &translation) override {
        Translation::divTranslationZ(translation);
        ACTION(x, x->divTranslationZ(translation);)
    }

    Magnum::Matrix4 translationZ() override {
        return Translation::translationZ();
    }

    void setTranslation(const float &x, const float &y, const float &z) override {
        Translation::setTranslation(x, y, z);
        ACTION(x_, x_->subTranslation(r_x, r_y, r_z); x_->addTranslation(x, y, z); )
    }

    void addTranslation(const float &x, const float &y, const float &z) override {
        Translation::addTranslation(x, y, z);
        ACTION(x_, x_->addTranslation(x, y, z);)
    }

    void subTranslation(const float &x, const float &y, const float &z) override {
        Translation::subTranslation(x, y, z);
        ACTION(x_, x_->subTranslation(x, y, z);)
    }

    void mulTranslation(const float &x, const float &y, const float &z) override {
        Translation::mulTranslation(x, y, z);
        ACTION(x_, x_->mulTranslation(x, y, z);)
    }

    void divTranslation(const float &x, const float &y, const float &z) override {
        Translation::divTranslation(x, y, z);
        ACTION(x_, x_->divTranslation(x, y, z);)
    }

    Magnum::Matrix4 translation() override {
        return Translation::translation();
    }
};

class Triangle_Solid : public DrawableObjectGroup {
    Triangle_Primitive *left, *right, *top_A, *top_B, *back_A, *back_B, *bottom_A, *bottom_B;

public:

    void init(const Magnum::Color3 & color) {
        left = createDrawableObject<Triangle_Primitive>("left");
        left->init(
                {-1, -1, 1},
                {1, -1, 1},
                {1, 1, 1},
                color
        );
        right = createDrawableObject<Triangle_Primitive>("right");
        right->init(
                {-1, -1, 1},
                {1, -1, 1},
                {-1, 1, 1},
                color
        );
        top_A = createDrawableObject<Triangle_Primitive>("top_A");
        top_A->init(
                {-1, -1, 1},
                {1, -1, 1},
                {1, 1, -1},
                color
        );
        top_B = createDrawableObject<Triangle_Primitive>("top_B");
        top_B->init(
                {-1, -1, 1},
                {1, 1, -1},
                {-1, 1, -1},
                color
        );
        back_A = createDrawableObject<Triangle_Primitive>("back_A");
        back_A->init(
                {-1, -1, 1},
                {1, -1, 1},
                {1, 1, 1},
                color
        );
        back_B = createDrawableObject<Triangle_Primitive>("back_B");
        back_B->init(
                {-1, -1, 1},
                {1, 1, 1},
                {-1, 1, 1},
                color
        );
        bottom_A = createDrawableObject<Triangle_Primitive>("bottom_A");
        bottom_A->init(
                {-1, -1, 1},
                {1, -1, -1},
                {1, -1, 1},
                color
        );
        bottom_B = createDrawableObject<Triangle_Primitive>("bottom_B");
        bottom_B->init(
                {-1, -1, 1},
                {-1, -1, -1},
                {1, -1, -1},
                color
        );

        right->addRotationY(180);
        top_A->addRotationY(-90);
        top_B->addRotationY(-90);
        back_A->addRotationY(90);
        back_B->addRotationY(90);
    }

    void draw(Crafter::Camera *mainCamera) const override {
        left->draw(mainCamera);
        right->draw(mainCamera);
        top_A->draw(mainCamera);
        top_B->draw(mainCamera);
        back_A->draw(mainCamera);
        back_B->draw(mainCamera);
        bottom_A->draw(mainCamera);
        bottom_B->draw(mainCamera);
    }
};

void Crafter::WorldEngine::WorldEngine::setup() {
    using namespace Magnum;
    using namespace Magnum::Math::Literals;

    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
}

void Crafter::WorldEngine::WorldEngine::attachToCamera(Crafter::Camera &camera) {
    this->camera = &camera;
//    this->camera->setRotation(30, 40, 0);
    this->camera->setTranslation(0, 0, 0);
}

void Crafter::WorldEngine::WorldEngine::rotateRelative(Magnum::Vector2 relative) {
    // rotate camera up, down, left, right
    camera->addRotationY((relative.x()*100));
    camera->addRotationX((relative.y()*100));
}

void Crafter::WorldEngine::WorldEngine::updateAspectRatio(float aspectRatio) {
    using namespace Magnum::Math::Literals;
    camera->setPerspectiveProjection(35.0_degf, aspectRatio, 0.01f, 100);
}

class Cube: public DrawableObject {
public:
    void init() {
        mesh = Magnum::MeshTools::compile(Magnum::Primitives::cubeSolid());
        addTranslationZ(-50);
        addRotationX(45);
        addRotationZ(14);
        shader = std::move(Magnum::Shaders::FlatGL3D{});
        using namespace Magnum::Math::Literals;
        shader.setColor(0xA1A1A1_rgbf);
    }

    void draw(Crafter::Camera *mainCamera) override {
        using namespace Magnum::Math::Literals;
        shader.setTransformationProjectionMatrix(projection_Type_OBJECT_TRANSLATION_IS_STATIC(mainCamera))
                .draw(mesh);
    }
};

class Grid: public DrawableObject {
public:
    void init() {
        mesh = Magnum::MeshTools::compile(Magnum::Primitives::grid3DWireframe({4, 4}));
        addRotationX(-90);
        addTranslationZ(-10);
        addTranslationY(-2);
        shader = std::move(Magnum::Shaders::FlatGL3D{});
        using namespace Magnum::Math::Literals;
        shader.setColor(0xA1A1A1_rgbf);
    }

    void draw(Crafter::Camera *mainCamera) override {
        using namespace Magnum::Math::Literals;
        shader.setTransformationProjectionMatrix(projection_Type_OBJECT_TRANSLATION_IS_STATIC(mainCamera))
                .draw(mesh);
    }
};

void Crafter::WorldEngine::WorldEngine::draw() {
    using namespace Magnum::Math::Literals;
    Cube cube; cube.init(); cube.draw(camera);
    Grid grid; grid.init(); grid.draw(camera);
    Triangle_Solid s;
    s.init(0xff0000_rgbf);
    s.addTranslationZ(-50);
    s.addTranslationX(3);
    s.addRotationX(42.5);
    s.draw(camera);
}