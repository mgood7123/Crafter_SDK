//
// Created by Matthew Good on 10/6/21.
//

#ifndef CRAFTER_EGL_CUBE_H
#define CRAFTER_EGL_CUBE_H

namespace Crafter {
    namespace Packages {
        class EGL_Cube : public Crafter::Package {
        public:
            CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_HPP(EGL_Cube);

            const GLfloat vertices[108] = {
                    // front
                    -0.5f, 0.5f, 0.5f,
                    -0.5f, -0.5f, 0.5f,
                    0.5f, 0.5f, 0.5f,
                    0.5f, 0.5f, 0.5f,
                    -0.5f, -0.5f, 0.5f,
                    0.5f, -0.5f, 0.5f,

                    // right
                    0.5f, 0.5f, 0.5f,
                    0.5f, -0.5f, 0.5f,
                    0.5f, 0.5f, -0.5f,
                    0.5f, 0.5f, -0.5f,
                    0.5f, -0.5f, 0.5f,
                    0.5f, -0.5f, -0.5f,

                    // back
                    0.5f, 0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    -0.5f, 0.5f, -0.5f,
                    -0.5f, 0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,

                    // left
                    -0.5f, 0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, 0.5f, 0.5f,
                    -0.5f, 0.5f, 0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, 0.5f,

                    // top
                    -0.5f, 0.5f, -0.5f,
                    -0.5f, 0.5f, 0.5f,
                    0.5f, 0.5f, -0.5f,
                    0.5f, 0.5f, -0.5f,
                    -0.5f, 0.5f, 0.5f,
                    0.5f, 0.5f, 0.5f,

                    // bottom
                    -0.5f, -0.5f, 0.5f,
                    -0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, 0.5f,
                    0.5f, -0.5f, 0.5f,
                    -0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f
            };

            const GLfloat colors[144] = {
                    // front
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,

                    // right
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,

                    // back
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,

                    // left
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,
                    0.0625f, 0.57421875f, 0.92578125f, 1.0f,

                    // top
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,
                    0.29296875f, 0.66796875f, 0.92578125f, 1.0f,

                    // bottom
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f,
                    0.52734375f, 0.76171875f, 0.92578125f, 1.0f
            };

            GLuint program;
            GLuint vertexID;
            GLuint colorID;

            GLuint mvpLoc;
            GLuint positionLoc;
            GLuint colorLoc;

            typedef struct {
                GLfloat mat[4][4];
            } glMatrix;

            glMatrix *projectionMat;
            glMatrix *modelviewMat;
            glMatrix *mvpMat;
            bool isInitialized;

            void multMatrix(glMatrix *result, glMatrix *srcA, glMatrix *srcB);

            void loadIdentity(glMatrix *result);

            void scaleMatrix(glMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz);

            void rotationMatrix(glMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

            void frustumMatrix(glMatrix *result, float left, float right, float bottom, float top,
                               float nearZ, float farZ);

            bool initialize();

            void render();

            void setup() override;

            void drawEvent() override;

            void viewportEvent(ViewportEvent &e) override;

            ~EGL_Cube();
        };
    }
}
#endif //CRAFTER_EGL_CUBE_H
