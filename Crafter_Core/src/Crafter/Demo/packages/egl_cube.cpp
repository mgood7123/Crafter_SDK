//
// Created by Matthew Good on 10/6/21.
//

CRAFTER_PACKAGE_CONSTRUCTOR_WRAPPERS_CPP(Crafter::Demo::Packages::EGL_Cube, EGL_Cube)

void
Crafter::Demo::Packages::EGL_Cube::multMatrix(glMatrix *result, glMatrix *srcA, glMatrix *srcB) {
    glMatrix    tmp;
    int         i;

    for (i=0; i<4; i++)
    {
        tmp.mat[i][0] = (srcA->mat[i][0] * srcB->mat[0][0]) +
                        (srcA->mat[i][1] * srcB->mat[1][0]) +
                        (srcA->mat[i][2] * srcB->mat[2][0]) +
                        (srcA->mat[i][3] * srcB->mat[3][0]) ;

        tmp.mat[i][1] = (srcA->mat[i][0] * srcB->mat[0][1]) +
                        (srcA->mat[i][1] * srcB->mat[1][1]) +
                        (srcA->mat[i][2] * srcB->mat[2][1]) +
                        (srcA->mat[i][3] * srcB->mat[3][1]) ;

        tmp.mat[i][2] = (srcA->mat[i][0] * srcB->mat[0][2]) +
                        (srcA->mat[i][1] * srcB->mat[1][2]) +
                        (srcA->mat[i][2] * srcB->mat[2][2]) +
                        (srcA->mat[i][3] * srcB->mat[3][2]) ;

        tmp.mat[i][3] = (srcA->mat[i][0] * srcB->mat[0][3]) +
                        (srcA->mat[i][1] * srcB->mat[1][3]) +
                        (srcA->mat[i][2] * srcB->mat[2][3]) +
                        (srcA->mat[i][3] * srcB->mat[3][3]) ;
    }
    memcpy(result, &tmp, sizeof(glMatrix));
}

void Crafter::Demo::Packages::EGL_Cube::loadIdentity(glMatrix *result) {
    memset(result, 0x0, sizeof(glMatrix));
    result->mat[0][0] = 1.0f;
    result->mat[1][1] = 1.0f;
    result->mat[2][2] = 1.0f;
    result->mat[3][3] = 1.0f;
}

void Crafter::Demo::Packages::EGL_Cube::scaleMatrix(glMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz) {
    result->mat[0][0] *= sx;
    result->mat[0][1] *= sx;
    result->mat[0][2] *= sx;
    result->mat[0][3] *= sx;

    result->mat[1][0] *= sy;
    result->mat[1][1] *= sy;
    result->mat[1][2] *= sy;
    result->mat[1][3] *= sy;

    result->mat[2][0] *= sz;
    result->mat[2][1] *= sz;
    result->mat[2][2] *= sz;
    result->mat[2][3] *= sz;
}

void
Crafter::Demo::Packages::EGL_Cube::rotationMatrix(glMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    GLfloat sinAngle, cosAngle;
    GLfloat mag = sqrtf(x * x + y * y + z * z);

    sinAngle = sin ( angle * M_PI / 180.0f );
    cosAngle = cos ( angle * M_PI / 180.0f );
    if ( mag > 0.0f )
    {
        GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
        GLfloat oneMinusCos;
        glMatrix rotMat;

        x /= mag;
        y /= mag;
        z /= mag;

        xx = x * x;
        yy = y * y;
        zz = z * z;
        xy = x * y;
        yz = y * z;
        zx = z * x;
        xs = x * sinAngle;
        ys = y * sinAngle;
        zs = z * sinAngle;
        oneMinusCos = 1.0f - cosAngle;

        rotMat.mat[0][0] = (oneMinusCos * xx) + cosAngle;
        rotMat.mat[0][1] = (oneMinusCos * xy) - zs;
        rotMat.mat[0][2] = (oneMinusCos * zx) + ys;
        rotMat.mat[0][3] = 0.0F;

        rotMat.mat[1][0] = (oneMinusCos * xy) + zs;
        rotMat.mat[1][1] = (oneMinusCos * yy) + cosAngle;
        rotMat.mat[1][2] = (oneMinusCos * yz) - xs;
        rotMat.mat[1][3] = 0.0F;

        rotMat.mat[2][0] = (oneMinusCos * zx) - ys;
        rotMat.mat[2][1] = (oneMinusCos * yz) + xs;
        rotMat.mat[2][2] = (oneMinusCos * zz) + cosAngle;
        rotMat.mat[2][3] = 0.0F;

        rotMat.mat[3][0] = 0.0F;
        rotMat.mat[3][1] = 0.0F;
        rotMat.mat[3][2] = 0.0F;
        rotMat.mat[3][3] = 1.0F;

        multMatrix( result, &rotMat, result );
    }
}

void Crafter::Demo::Packages::EGL_Cube::frustumMatrix(glMatrix *result, float left, float right, float bottom,
                                                float top, float nearZ, float farZ) {
    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;
    glMatrix    frust;

    if ( (nearZ <= 0.0f) || (farZ <= 0.0f) ||
         (deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f) )
        return;

    frust.mat[0][0] = 2.0f * nearZ / deltaX;
    frust.mat[0][1] = frust.mat[0][2] = frust.mat[0][3] = 0.0f;

    frust.mat[1][1] = 2.0f * nearZ / deltaY;
    frust.mat[1][0] = frust.mat[1][2] = frust.mat[1][3] = 0.0f;

    frust.mat[2][0] = (right + left) / deltaX;
    frust.mat[2][1] = (top + bottom) / deltaY;
    frust.mat[2][2] = -(nearZ + farZ) / deltaZ;
    frust.mat[2][3] = -1.0f;

    frust.mat[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.mat[3][0] = frust.mat[3][1] = frust.mat[3][3] = 0.0f;

    multMatrix(result, &frust, result);
}

bool Crafter::Demo::Packages::EGL_Cube::initialize() {
    glClearDepthf(1.0f);
    glClearColor(0.0f,0.0f,0.0f,1.0f);

    glEnable(GL_CULL_FACE);

    const char* vSource =
            "precision mediump float;"
            "uniform mat4 u_mvpMat;"
            "attribute vec4 a_position;"
            "attribute vec4 a_color;"
            "varying vec4 v_color;"
            "void main()"
            "{"
            "gl_Position = u_mvpMat * a_position;"
            "v_color = a_color;"
            "}";

    const char* fSource =
            "varying lowp vec4 v_color;"
            "void main()"
            "{"
            "    gl_FragColor = v_color;"
            "}";

    GLint status;

// Compile the vertex shader
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    if (!vs) {
        Error{} << "Failed to create vertex shader: " << glGetError();
        return false;
    } else {
        glShaderSource(vs, 1, &vSource, 0);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
        if (GL_FALSE == status) {
            GLchar log[256];
            glGetShaderInfoLog(vs, 256, NULL, log);

            Error{} << "Failed to compile vertex shader: " << log;

            glDeleteShader(vs);
        }
    }

// Compile the fragment shader
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fs) {
        Error{} << "Failed to create fragment shader: " << glGetError();
        return false;
    } else {
        glShaderSource(fs, 1, &fSource, 0);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
        if (GL_FALSE == status) {
            GLchar log[256];
            glGetShaderInfoLog(fs, 256, NULL, log);

            Error{} << "Failed to compile fragment shader: " << log;

            glDeleteShader(vs);
            glDeleteShader(fs);

            return false;
        }
    }

    // Create and link the program
    program = glCreateProgram();
    if (program)
    {
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)    {
            GLchar log[256];
            glGetProgramInfoLog(fs, 256, NULL, log);

            Error{} << "Failed to link shader program: " << log;

            glDeleteProgram(program);
            program = 0;

            return false;
        }
    } else {
        Error{} << "Failed to create a shader program";

        glDeleteShader(vs);
        glDeleteShader(fs);
        return false;
    }

// We don't need the shaders anymore - the program is enough
    glDeleteShader(fs);
    glDeleteShader(vs);

    mvpLoc = glGetUniformLocation(program, "u_mvpMat");
    positionLoc = glGetAttribLocation(program, "a_position");
    colorLoc = glGetAttribLocation(program, "a_color");

    // Generate vertex and color buffers and fill with data
    glGenBuffers(1, &vertexID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                 GL_STATIC_DRAW);

    glGenBuffers(1, &colorID);
    glBindBuffer(GL_ARRAY_BUFFER, colorID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors,
                 GL_STATIC_DRAW);

    projectionMat = new glMatrix;
    modelviewMat = new glMatrix;
    mvpMat = new glMatrix;
    loadIdentity( projectionMat );
    loadIdentity( modelviewMat );

    return true;
}

void Crafter::Demo::Packages::EGL_Cube::viewportEvent(ViewportEvent &e) {
    int surface_width = e.windowSize().x();
    int surface_height = e.windowSize().y();
    glViewport(0, 0, surface_width, surface_height);
    GLfloat aspect = (float)surface_width/(float)surface_height;
    GLfloat near = -2.0f;
    GLfloat far  = 2.0f;
    GLfloat yFOV  = 75.0f;
    GLfloat height = tanf( yFOV / 360.0f * M_PI ) * near;
    GLfloat width = height * aspect;


    frustumMatrix( projectionMat, -width, width, -height, height, near,
                   far );

    if ( surface_width > surface_height ){
        scaleMatrix( projectionMat, (float)surface_height/(float)surface_width,
                     1.0f, 1.0f );
    } else {
        scaleMatrix( projectionMat, 1.0f,
                     (float)surface_width/(float)surface_height, 1.0f );
    }
}

void Crafter::Demo::Packages::EGL_Cube::setup() {
    isInitialized = initialize();
    if (isInitialized) {
        glUseProgram(program);
        // Enable and bind the vertex information
        glEnableVertexAttribArray(positionLoc);
        glBindBuffer(GL_ARRAY_BUFFER, vertexID);
        glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE,
                              3 * sizeof(GLfloat), 0);

        // Enable and bind the color information
        glEnableVertexAttribArray(colorLoc);
        glBindBuffer(GL_ARRAY_BUFFER, colorID);
        glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE,
                              4 * sizeof(GLfloat), 0);
    }
}

void Crafter::Demo::Packages::EGL_Cube::drawEvent() {
    if (isInitialized) render();
}

void Crafter::Demo::Packages::EGL_Cube::render() {

    //Typical render pass
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rotationMatrix( modelviewMat, 1.0f, -1.0f, -1.0f, 0.0f);
    multMatrix( mvpMat, modelviewMat, projectionMat);
    glUniformMatrix4fv(mvpLoc, 1, false, &mvpMat->mat[0][0]);

    // Same draw call as in GLES1.
    glDrawArrays(GL_TRIANGLES, 0 , 36);

    swapBuffers();
    redraw();
}

Crafter::Demo::Packages::EGL_Cube::~EGL_Cube() {
    // Disable attribute arrays
    glDisableVertexAttribArray(positionLoc);
    glDisableVertexAttribArray(colorLoc);
    glDeleteProgram(program);
    delete projectionMat;
    delete modelviewMat;
    delete mvpMat;
}