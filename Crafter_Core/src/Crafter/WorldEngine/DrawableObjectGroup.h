//
// Created by Matthew Good on 16/6/21.
//

#ifndef CRAFTER_DRAWABLEOBJECTGROUP_H
#define CRAFTER_DRAWABLEOBJECTGROUP_H

#include <type_traits>
#include <Crafter/WorldEngine/WINAPI_KERNEL/SDK/include/Windows/Kernel/WindowsAPIKernel.h>
#include "DrawableObject.h"

namespace Crafter {
    namespace WorldEngine {
        class DrawableObjectGroup : public WorldSpace {
            Kernel kernel;
            class KEY {
            public:
                const char *key;
                AnyOpt drawableObject;
                AnyOpt drawableObjectGroup;

                KEY(const char *key, AnyOpt drawableObject, AnyOpt drawableObjectGroup) {
                    this->key = key;
                    this->drawableObject = drawableObject;
                    this->drawableObjectGroup = drawableObjectGroup;
                }
            };

        public:
            Object *find_key(const char *key, size_t resource_len) {
                int page = 1;
                size_t index = 0;
                size_t page_size = kernel.table->page_size;
                for (; page <= kernel.table->Page.count(); page++) {
                    index = ((page_size * page) - page_size);
                    for (; index < page_size * page; index++)
                        if (kernel.table->table[index] != nullptr) {
                            Object *object = kernel.table->table[index];
                            KEY *key_ = object->resource.get<KEY *>();
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

            Object *find_key(const char *key) {
                return find_key(key, strlen(key));
            }

            template<typename T>
            T *createDrawableObject() {
                static_assert(std::is_convertible<T, DrawableObject>::value,
                              "T must extend DrawableObject: change 'class T { /* ... */ }' to 'class T: public Crafter::WorldEngine::DrawableObject { /* ... */ }'");
                Object *o = kernel
                        .newObject(ObjectTypeNone, ObjectFlagNone, KEY{nullptr, T(), AnyNullOpt});
                return o == nullptr ? nullptr : o->resource.get<KEY *>()->drawableObject.get<T *>();
            }

            template<typename T>
            T *createDrawableObject(const char *key) {
                static_assert(std::is_convertible<T, DrawableObject>::value,
                              "T must extend DrawableObject: change 'class T { /* ... */ }' to 'class T: public Crafter::WorldEngine::DrawableObject { /* ... */ }'");
                Object *o = kernel
                        .newObject(ObjectTypeNone, ObjectFlagNone, KEY{key, T(), AnyNullOpt});
                return o == nullptr ? nullptr : o->resource.get<KEY *>()->drawableObject.get<T *>();
            }

            template<typename T>
            T *getDrawableObject(const char *key) {
                static_assert(std::is_convertible<T, DrawableObject>::value,
                              "T must extend DrawableObject: change 'class T { /* ... */ }' to 'class T: public Crafter::WorldEngine::DrawableObject { /* ... */ }'");
                Object *o = find_key(key);
                if (o == nullptr) return nullptr;
                return o->resource.get<KEY *>()->drawableObject.get<T *>();
            }

            void AddDrawableObjectGroup(const char *key, DrawableObjectGroup *drawableObjectGroup) {
                kernel.newObject(ObjectTypeNone, ObjectFlagNone,
                                 KEY{key, AnyNullOpt, drawableObjectGroup});
            }

            DrawableObjectGroup *getDrawableObjectGroup(const char *key) {
                Object *o = find_key(key);
                if (o == nullptr) return nullptr;
                return o->resource.get<KEY *>()->drawableObjectGroup.get<DrawableObjectGroup *>();
            }

#define DrawableObjectGroup_ACTION(DrawableObject_PTR, CODE) { \
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

            virtual void draw(Crafter::Camera *mainCamera) {
                DrawableObjectGroup_ACTION(x, x->draw(mainCamera);)
            }

            void saveTranslationX() override {
                WorldSpace::saveTranslationX();
                DrawableObjectGroup_ACTION(x, x->saveTranslationX();)
            }

            void saveTranslationY() override {
                WorldSpace::saveTranslationY();
                DrawableObjectGroup_ACTION(x, x->saveTranslationY();)
            }

            void saveTranslationZ() override {
                WorldSpace::saveTranslationZ();
                DrawableObjectGroup_ACTION(x, x->saveTranslationZ();)
            }

            void saveTranslation() override {
                WorldSpace::saveTranslation();
                DrawableObjectGroup_ACTION(x, x->saveTranslation();)
            }

            void restoreTranslationX() override {
                WorldSpace::restoreTranslationX();
                DrawableObjectGroup_ACTION(x, x->restoreTranslationX();)
            }

            void restoreTranslationY() override {
                WorldSpace::restoreTranslationY();
                DrawableObjectGroup_ACTION(x, x->restoreTranslationY();)
            }

            void restoreTranslationZ() override {
                WorldSpace::restoreTranslationZ();
                DrawableObjectGroup_ACTION(x, x->restoreTranslationZ();)
            }

            void restoreTranslation() override {
                WorldSpace::restoreTranslation();
                DrawableObjectGroup_ACTION(x, x->restoreTranslation();)
            }

            void setTranslationX(const float &translation) override {
                WorldSpace::setTranslationX(translation);
                DrawableObjectGroup_ACTION(x, x->subTranslationX(model_matrix.t_x); x->addTranslationX(translation);)
            }

            void addTranslationX(const float &translation) override {
                WorldSpace::addTranslationX(translation);
                DrawableObjectGroup_ACTION(x, x->addTranslationX(translation);)
            }

            void subTranslationX(const float &translation) override {
                WorldSpace::subTranslationX(translation);
                DrawableObjectGroup_ACTION(x, x->subTranslationX(translation);)
            }

            void mulTranslationX(const float &translation) override {
                WorldSpace::mulTranslationX(translation);
                DrawableObjectGroup_ACTION(x, x->mulTranslationX(translation);)
            }

            void divTranslationX(const float &translation) override {
                WorldSpace::divTranslationX(translation);
                DrawableObjectGroup_ACTION(x, x->divTranslationX(translation);)
            }

            void setTranslationY(const float &translation) override {
                WorldSpace::setTranslationY(translation);
                DrawableObjectGroup_ACTION(x, x->subTranslationY(model_matrix.t_y); x->addTranslationY(translation);)
            }

            void addTranslationY(const float &translation) override {
                WorldSpace::addTranslationY(translation);
                DrawableObjectGroup_ACTION(x, x->addTranslationY(translation);)
            }

            void subTranslationY(const float &translation) override {
                WorldSpace::subTranslationY(translation);
                DrawableObjectGroup_ACTION(x, x->subTranslationY(translation);)
            }

            void mulTranslationY(const float &translation) override {
                WorldSpace::mulTranslationY(translation);
                DrawableObjectGroup_ACTION(x, x->mulTranslationY(translation);)
            }

            void divTranslationY(const float &translation) override {
                WorldSpace::divTranslationY(translation);
                DrawableObjectGroup_ACTION(x, x->divTranslationY(translation);)
            }

            void setTranslationZ(const float &translation) override {
                WorldSpace::setTranslationX(translation);
                DrawableObjectGroup_ACTION(x, x->subTranslationZ(model_matrix.t_z); x->addTranslationZ(translation);)
            }

            void addTranslationZ(const float &translation) override {
                WorldSpace::addTranslationZ(translation);
                DrawableObjectGroup_ACTION(x, x->addTranslationZ(translation);)
            }

            void subTranslationZ(const float &translation) override {
                WorldSpace::subTranslationZ(translation);
                DrawableObjectGroup_ACTION(x, x->setTranslationZ(translation);)
            }

            void mulTranslationZ(const float &translation) override {
                WorldSpace::mulTranslationZ(translation);
                DrawableObjectGroup_ACTION(x, x->mulTranslationZ(translation);)
            }

            void divTranslationZ(const float &translation) override {
                WorldSpace::divTranslationZ(translation);
                DrawableObjectGroup_ACTION(x, x->divTranslationZ(translation);)
            }

            void setTranslation(const float &x, const float &y, const float &z) override {
                WorldSpace::setTranslation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->subTranslation(model_matrix.t_x, model_matrix.t_y, model_matrix.t_z); x_->addTranslation(x, y, z);)
            }

            void addTranslation(const float &x, const float &y, const float &z) override {
                WorldSpace::addTranslation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->addTranslation(x, y, z);)
            }

            void subTranslation(const float &x, const float &y, const float &z) override {
                WorldSpace::subTranslation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->subTranslation(x, y, z);)
            }

            void mulTranslation(const float &x, const float &y, const float &z) override {
                WorldSpace::mulTranslation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->mulTranslation(x, y, z);)
            }

            void divTranslation(const float &x, const float &y, const float &z) override {
                WorldSpace::divTranslation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->divTranslation(x, y, z);)
            }

            void saveScaleX() override {
                WorldSpace::saveScaleX();
                DrawableObjectGroup_ACTION(x, x->saveScaleX();)
            }

            void saveScaleY() override {
                WorldSpace::saveScaleY();
                DrawableObjectGroup_ACTION(x, x->saveScaleY();)
            }

            void saveScaleZ() override {
                WorldSpace::saveScaleZ();
                DrawableObjectGroup_ACTION(x, x->saveScaleZ();)
            }

            void saveScale() override {
                WorldSpace::saveScale();
                DrawableObjectGroup_ACTION(x, x->saveScale();)
            }

            void restoreScaleX() override {
                WorldSpace::restoreScaleX();
                DrawableObjectGroup_ACTION(x, x->restoreScaleX();)
            }

            void restoreScaleY() override {
                WorldSpace::restoreScaleY();
                DrawableObjectGroup_ACTION(x, x->restoreScaleY();)
            }

            void restoreScaleZ() override {
                WorldSpace::restoreScaleZ();
                DrawableObjectGroup_ACTION(x, x->restoreScaleZ();)
            }

            void restoreScale() override {
                WorldSpace::restoreScale();
                DrawableObjectGroup_ACTION(x, x->restoreScale();)
            }

            void setScaleX(const float &degrees) override {
                WorldSpace::setScaleX(degrees);
                DrawableObjectGroup_ACTION(x, x->subScaleX(model_matrix.s_x); x->addScaleX(degrees);)
            }

            void addScaleX(const float &degrees) override {
                WorldSpace::addScaleX(degrees);
                DrawableObjectGroup_ACTION(x, x->addScaleX(degrees);)
            }

            void subScaleX(const float &degrees) override {
                WorldSpace::subScaleX(degrees);
                DrawableObjectGroup_ACTION(x, x->subScaleX(degrees);)
            }

            void mulScaleX(const float &degrees) override {
                WorldSpace::mulScaleX(degrees);
                DrawableObjectGroup_ACTION(x, x->mulScaleX(degrees);)
            }

            void divScaleX(const float &degrees) override {
                WorldSpace::divScaleX(degrees);
                DrawableObjectGroup_ACTION(x, x->divScaleX(degrees);)
            }

            void setScaleY(const float &degrees) override {
                WorldSpace::setScaleY(degrees);
                DrawableObjectGroup_ACTION(x, x->subScaleY(model_matrix.s_y); x->addScaleY(degrees);)
            }

            void addScaleY(const float &degrees) override {
                WorldSpace::addScaleY(degrees);
                DrawableObjectGroup_ACTION(x, x->addScaleY(degrees);)
            }

            void subScaleY(const float &degrees) override {
                WorldSpace::subScaleY(degrees);
                DrawableObjectGroup_ACTION(x, x->subScaleY(degrees);)
            }

            void mulScaleY(const float &degrees) override {
                WorldSpace::mulScaleY(degrees);
                DrawableObjectGroup_ACTION(x, x->mulScaleY(degrees);)
            }

            void divScaleY(const float &degrees) override {
                WorldSpace::divScaleY(degrees);
                DrawableObjectGroup_ACTION(x, x->divScaleY(degrees);)
            }

            void setScaleZ(const float &degrees) override {
                WorldSpace::setScaleX(degrees);
                DrawableObjectGroup_ACTION(x, x->subScaleZ(model_matrix.s_z); x->addScaleZ(degrees);)
            }

            void addScaleZ(const float &degrees) override {
                WorldSpace::addScaleZ(degrees);
                DrawableObjectGroup_ACTION(x, x->addScaleZ(degrees);)
            }

            void subScaleZ(const float &degrees) override {
                WorldSpace::subScaleZ(degrees);
                DrawableObjectGroup_ACTION(x, x->setScaleZ(degrees);)
            }

            void mulScaleZ(const float &degrees) override {
                WorldSpace::mulScaleZ(degrees);
                DrawableObjectGroup_ACTION(x, x->mulScaleZ(degrees);)
            }

            void divScaleZ(const float &degrees) override {
                WorldSpace::divScaleZ(degrees);
                DrawableObjectGroup_ACTION(x, x->divScaleZ(degrees);)
            }

            void setScale(const float &x, const float &y, const float &z) override {
                WorldSpace::setScale(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->subScale(model_matrix.s_x, model_matrix.s_y, model_matrix.s_z); x_->addScale(x, y, z);)
            }

            void addScale(const float &x, const float &y, const float &z) override {
                WorldSpace::addScale(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->addScale(x, y, z);)
            }

            void subScale(const float &x, const float &y, const float &z) override {
                WorldSpace::subScale(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->subScale(x, y, z);)
            }

            void mulScale(const float &x, const float &y, const float &z) override {
                WorldSpace::mulScale(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->mulScale(x, y, z);)
            }

            void divScale(const float &x, const float &y, const float &z) override {
                WorldSpace::divScale(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->divScale(x, y, z);)
            }

            void saveRotationX() override {
                WorldSpace::saveRotationX();
                DrawableObjectGroup_ACTION(x, x->saveRotationX();)
            }

            void saveRotationY() override {
                WorldSpace::saveRotationY();
                DrawableObjectGroup_ACTION(x, x->saveRotationY();)
            }

            void saveRotationZ() override {
                WorldSpace::saveRotationZ();
                DrawableObjectGroup_ACTION(x, x->saveRotationZ();)
            }

            void saveRotation() override {
                WorldSpace::saveRotation();
                DrawableObjectGroup_ACTION(x, x->saveRotation();)
            }

            void restoreRotationX() override {
                WorldSpace::restoreRotationX();
                DrawableObjectGroup_ACTION(x, x->restoreRotationX();)
            }

            void restoreRotationY() override {
                WorldSpace::restoreRotationY();
                DrawableObjectGroup_ACTION(x, x->restoreRotationY();)
            }

            void restoreRotationZ() override {
                WorldSpace::restoreRotationZ();
                DrawableObjectGroup_ACTION(x, x->restoreRotationZ();)
            }

            void restoreRotation() override {
                WorldSpace::restoreRotation();
                DrawableObjectGroup_ACTION(x, x->restoreRotation();)
            }

            void setRotationX(const float &degrees) override {
                WorldSpace::setRotationX(degrees);
                DrawableObjectGroup_ACTION(x, x->subRotationX(model_matrix.r_x); x->addRotationX(degrees);)
            }

            void addRotationX(const float &degrees) override {
                WorldSpace::addRotationX(degrees);
                DrawableObjectGroup_ACTION(x, x->addRotationX(degrees);)
            }

            void subRotationX(const float &degrees) override {
                WorldSpace::subRotationX(degrees);
                DrawableObjectGroup_ACTION(x, x->subRotationX(degrees);)
            }

            void mulRotationX(const float &degrees) override {
                WorldSpace::mulRotationX(degrees);
                DrawableObjectGroup_ACTION(x, x->mulRotationX(degrees);)
            }

            void divRotationX(const float &degrees) override {
                WorldSpace::divRotationX(degrees);
                DrawableObjectGroup_ACTION(x, x->divRotationX(degrees);)
            }

            void setRotationY(const float &degrees) override {
                WorldSpace::setRotationY(degrees);
                DrawableObjectGroup_ACTION(x, x->subRotationY(model_matrix.r_y); x->addRotationY(degrees);)
            }

            void addRotationY(const float &degrees) override {
                WorldSpace::addRotationY(degrees);
                DrawableObjectGroup_ACTION(x, x->addRotationY(degrees);)
            }

            void subRotationY(const float &degrees) override {
                WorldSpace::subRotationY(degrees);
                DrawableObjectGroup_ACTION(x, x->subRotationY(degrees);)
            }

            void mulRotationY(const float &degrees) override {
                WorldSpace::mulRotationY(degrees);
                DrawableObjectGroup_ACTION(x, x->mulRotationY(degrees);)
            }

            void divRotationY(const float &degrees) override {
                WorldSpace::divRotationY(degrees);
                DrawableObjectGroup_ACTION(x, x->divRotationY(degrees);)
            }

            void setRotationZ(const float &degrees) override {
                WorldSpace::setRotationX(degrees);
                DrawableObjectGroup_ACTION(x, x->subRotationZ(model_matrix.r_z); x->addRotationZ(degrees);)
            }

            void addRotationZ(const float &degrees) override {
                WorldSpace::addRotationZ(degrees);
                DrawableObjectGroup_ACTION(x, x->addRotationZ(degrees);)
            }

            void subRotationZ(const float &degrees) override {
                WorldSpace::subRotationZ(degrees);
                DrawableObjectGroup_ACTION(x, x->setRotationZ(degrees);)
            }

            void mulRotationZ(const float &degrees) override {
                WorldSpace::mulRotationZ(degrees);
                DrawableObjectGroup_ACTION(x, x->mulRotationZ(degrees);)
            }

            void divRotationZ(const float &degrees) override {
                WorldSpace::divRotationZ(degrees);
                DrawableObjectGroup_ACTION(x, x->divRotationZ(degrees);)
            }

            void setRotation(const float &x, const float &y, const float &z) override {
                WorldSpace::setRotation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->subRotation(model_matrix.r_x, model_matrix.r_y, model_matrix.r_z); x_->addRotation(x, y, z);)
            }

            void addRotation(const float &x, const float &y, const float &z) override {
                WorldSpace::addRotation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->addRotation(x, y, z);)
            }

            void subRotation(const float &x, const float &y, const float &z) override {
                WorldSpace::subRotation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->subRotation(x, y, z);)
            }

            void mulRotation(const float &x, const float &y, const float &z) override {
                WorldSpace::mulRotation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->mulRotation(x, y, z);)
            }

            void divRotation(const float &x, const float &y, const float &z) override {
                WorldSpace::divRotation(x, y, z);
                DrawableObjectGroup_ACTION(x_, x_->divRotation(x, y, z);)
            }

            virtual void setColor(unsigned long long color) {
                setColor(Magnum::Math::Literals::operator ""_rgbf(color));
            }

            virtual void setColor(Magnum::Color3 color) {
                DrawableObjectGroup_ACTION(x, x->setColor(color);)
            }

    #undef DrawableObjectGroup_ACTION
        };
    }
}
#endif //CRAFTER_DRAWABLEOBJECTGROUP_H
