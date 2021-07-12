using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SharpGL;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Collections;
using System.Diagnostics;

namespace DM_CalibrationTools
{
    class csgl
    {
        private OpenGL glInstance;
        private  OpenGLControl scInstance;
        public OpenGL getGlInstance(){ return glInstance;}
        int mouseX;
        int mouseY;
        public bool Global_MouseDown = false;
        public bool Global_MouseInGLPanel = false;
        double[] matrixProjection = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        const float DEG2RAD = 3.141593f / 180;
        const float FOV_Y = 120.0f;              // vertical FOV in degree
        const float NEAR_PLANE = 1.0f;
        const float FAR_PLANE = 100.0f;

        /* 初始摄像头位置以及姿态的设置 */
        const float CAMERA_ANGLE_X = 45.0f;     // 摄像头的俯仰角
        const float CAMERA_ANGLE_Y = 0.0f;     // 摄像头偏航角
        const float CAMERA_DISTANCE = 30.0f;     // 摄像头距离
        const float CAMERA_HIGHT = -3.0f;



        float cameraAngleX;
        float cameraAngleY;
        float cameraHight;
        float cameraDistance;
        double[] modelview = { 0.7071068, 0.5, -0.5, 0, 0, 0.7071068, 0.7071068, 0, 0.7071068, -0.0, 0.5, 0, 0, 0, -25, 1 };
        bool drawModeChanged;
        int drawMode;

        float[] cameraPosition = { 0, 0, 0 };
        float[] cameraAngle = { 0, 0, 0 };
        float[] modelPosition = { 0, 0, 0 };
        float[] modelAngle = { 0, 0, 0 };


        float[] bgColor = { 0, 0, 0, 0};



        public csgl(OpenGLControl sc)
        {
            scInstance=sc;
            glInstance = sc.OpenGL;
            cameraAngleX = CAMERA_ANGLE_X;
            cameraAngleY = CAMERA_ANGLE_Y;
            cameraHight = CAMERA_HIGHT;
            cameraDistance = CAMERA_DISTANCE;

            drawModeChanged = false;
            drawMode = 0;
            DrawFlag = 2;
            Initialized();

        }
        ArrayList list = new ArrayList();
        public void addPoint(double x, double y, double z)
        {
            list.Add(new double[] { x, y, z }); 
        }
        public void resetPoint()
        {
            list.Clear();
        }
        HashSet<double []> poinths;
        public void setPoinths(HashSet<double []> hs)
        {
            poinths = hs;
        }
        double[][] pointarr;
        public void setPointarr(HashSet<double[]> hs)
        {
            pointarr = new double[hs.Count][];
            hs.CopyTo(pointarr);
        }
         public void DrawPoints(OpenGL gl,float r = 0.1f)
         {

             if (pointarr == null) 
             {
                // Debug.WriteLine("pointarr == null");
                 return;
             }
                 foreach (double[] v in pointarr)
                 {
                     DrawPoint(gl, v[0] * 0.04, v[1] * 0.04, v[2] * 0.04);
                 }
         }
        public void DrawPoint(OpenGL gl,double x, double y, double z, float r = 0.05f)
        {
             gl.PushMatrix();
//             gl.Translate(modelPosition[0], modelPosition[1], modelPosition[2]);
            gl.Translate(x, y, z);
            gl.Color(1.0,1.0,1.0);
            auxSolidSphere(r);
            gl.PopMatrix();
        }
        public void drawAxis(float size)
        {
            OpenGL gl = glInstance;
            //gl.Disable(OpenGL.GL_TEXTURE_2D);
            //gl.DepthFunc(OpenGL.GL_ALWAYS);     // to avoid visual artifacts with grid lines
            gl.Disable(OpenGL.GL_LIGHTING);
           // gl.PushMatrix();             //NOTE: There is a bug on Mac misbehaviours of
            //      the light position when you draw GL_LINES
            //      and GL_POINTS. remember the matrix.
            // draw axis
            gl.LineWidth(5);
            gl.Begin(OpenGL.GL_LINES);
            gl.Color(1.0, 0, 0);
            gl.Vertex(0, 0, 0);
            gl.Vertex(size, 0, 0);
            gl.Color(0, 1.0, 0);
            gl.Vertex(0, 0, 0);
            gl.Vertex(0, size, 0);
            gl.Color(0, 0, 1.0);
            gl.Vertex(0, 0, 0);
            gl.Vertex(0, 0, size);
            gl.End();
            gl.LineWidth(1);

            // draw arrows(actually big square dots)
//             gl.PointSize(12);
//             gl.Begin(OpenGL.GL_POINTS);
//             gl.Color(1.0, 0, 0);
//             gl.Vertex(size, 0, 0);
//             gl.Color(0, 1.0, 0);
//             gl.Vertex(0, size, 0);
//             gl.Color(0, 0, 1.0);
//             gl.Vertex(0, 0, size);
//             gl.End();
//             gl.PointSize(1);
            gl.PushMatrix();
            IntPtr  gluNewQuadric = gl.NewQuadric();
            gl.QuadricNormals(gluNewQuadric, OpenGL.GLU_SMOOTH);
             //画圆锥
            //创建二次曲面对象,X轴的箭头
            gl.Translate(size, 0f, 0f); 
            gl.Rotate(90, 0.0f, 1.0f, 0.0f);
            gl.Color(1.0f, 0.0f, 0.0f);			// Red
            gl.Cylinder(gluNewQuadric, 0.5f, 0.0f, 0.5f, 32, 320);
            gl.Rotate(-90, 0.0f, 1.0f, 0.0f);
            gl.Translate(-size, 0f, 0f); 
            //创建二次曲面对象,Y轴的箭头
            gl.Translate(0f, size, 0f); 
            gl.Rotate(-90, 1.0f, 0.0f, 0.0f);
            gl.Color(0.0f, 1.0f, 0.0f);			// Green
            gl.Cylinder(gluNewQuadric, 0.5f, 0.0f, 0.5f, 32, 32);
            gl.Rotate(90, 1.0f, 0.0f, 0.0f);
            gl.Translate(0f, -size, 0f);
            //创建二次曲面对象,Z轴的箭头
            gl.Translate(0f, 0f, size);
            gl.Color(0.0f, 0.0f, 1.0f);			// Blue
            gl.Cylinder(gluNewQuadric, 0.5f, 0.0f, 0.5f, 32, 32);
            gl.Translate(0f, 0f, -size); 
            //在这里绘制坐标系统
            // restore default settings
            gl.PopMatrix();
            gl.Enable(OpenGL.GL_LIGHTING);
            //gl.DepthFunc(OpenGL.GL_LEQUAL);
        }
        public void Draw()
        {
            OpenGL gl = glInstance;
            // set bottom viewport
            setViewportSub(0, 0, scInstance.Width, scInstance.Height, NEAR_PLANE, FAR_PLANE);

            // clear buffer
            //gl.ClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);   // background color
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT | OpenGL.GL_STENCIL_BUFFER_BIT);
            gl.LoadIdentity();
            //gl.PushMatrix();

            // First, transform the camera (viewing matrix) from world space to eye space
            gl.Translate(0, cameraHight, -cameraDistance);
            //move camera

            gl.Translate(cameraPosition[0], cameraPosition[1], cameraPosition[2]);

            gl.Rotate(cameraAngleX, 1, 0, 0); // pitch
            gl.Rotate(cameraAngleY, 0, 1, 0); // heading

            // draw grid
            drawGrid(300, 1);

            // draw a teapot
            gl.PushMatrix();
            gl.Translate(modelPosition[0], modelPosition[1], modelPosition[2]);
            gl.PopMatrix();

            if (DrawFlag == 1)
            {
                DrawPoints(gl);
            }
            else if(DrawFlag==2)
            {
                
               // mVector3 v = CaliAPI.GetEulerianAngle();
                gl.PushMatrix();
//                 gl.Rotate(v.y, 1, 0, 0); // pitch
//                 gl.Rotate(v.x, 0, 0, -1); // pitch
//                 gl.Rotate(90, 0, 1, 0); // heading
                Quaternion q =CaliAPI.GetQuaternion();
                double halfsita = Math.Acos(q.w);
                double nx = q.y / Math.Sin(halfsita);
                double ny = q.z / Math.Sin(halfsita);
                double nz = q.x/ Math.Sin(halfsita);
                double SitaAngle = halfsita * 2 * (180.0f / 3.141592f);
                //gl.Rotate(45, 0, 0);
                gl.Rotate( 0, 90, 90f);
                gl.Rotate(0, 0, 0);

                gl.Rotate(SitaAngle, nx, ny, nz);
                //gl.Rotate(SitaAngle, ny,nz,nx);               
                drawAxis(20);
                DrawCube();
                gl.PopMatrix();
               
            }
//             else
//             {
//                 drawAxis(20);
//             }



            //gl.PopMatrix();



        }
        public void resize()
        {
            OpenGL gl = getGlInstance();

            //  设置当前矩阵模式,对投影矩阵应用随后的矩阵操作
            gl.MatrixMode(OpenGL.GL_PROJECTION);

            // 重置当前指定的矩阵为单位矩阵,将当前的用户坐标系的原点移到了屏幕中心
            gl.LoadIdentity();
            // 创建透视投影变换
            gl.Perspective(FOV_Y, scInstance.Width/ scInstance.Height, 5, 100.0);

            // 视点变换
            gl.LookAt(-5, 5, -5, 0, 0, 0, 0, 1, 0);

            // 设置当前矩阵为模型视图矩阵
            gl.MatrixMode(OpenGL.GL_MODELVIEW);
        }
        void auxSolidSphere(float p)
        {
            drawSphere(p);
            return;
//             OpenGL gl = getGlInstance();
// 
//             gl.Color(0.5f, 0.5f, 0.5f);    /**< 灰色 */
//             gl.Scale(p, p, p);
//             DrawCube(gl);


        }
        public void drawSphere(double radius, int segx = 40, int segy = 40, bool isLines = false)
        {
            float x = 0, y = 0, z = 0;
            OpenGL gl = getGlInstance();
            gl.PushMatrix();
            gl.Translate(x, y, z);
            var sphere = gl.NewQuadric();
            if (isLines)
                gl.QuadricDrawStyle(sphere, OpenGL.GL_LINES);
            else
                gl.QuadricDrawStyle(sphere, OpenGL.GL_QUADS);
            gl.QuadricNormals(sphere, OpenGL.GLU_SMOOTH);   //GLU_NONE,GLU_FLAT,GLU_SMOOTH
            gl.QuadricOrientation(sphere, (int)OpenGL.GLU_OUTSIDE);  //GLU_OUTSIDE,GLU_INSIDE
            gl.QuadricTexture(sphere, (int)OpenGL.GLU_FALSE);  //GL_TRUE,GLU_FALSE
            gl.Sphere(sphere, radius, segx, segy);
            gl.DeleteQuadric(sphere);
            gl.PopMatrix();
        }
        public void DrawCube()
        {
            OpenGL gl = glInstance;
            gl.PushMatrix();
            
            // OpenGL gl = getGlInstance();
            gl.Begin(OpenGL.GL_QUADS);
            
            gl.Color(1.0, 0, 0);
            gl.Vertex(-10.0f, -10.0f, -10.0f);
            gl.Vertex(-10.0f, 10.0f, -10.0f);
            gl.Vertex(10.0f, 10.0f, -10.0f);
            gl.Vertex(10.0f, -10.0f, -10.0f);

            gl.Color(1.0, 1, 0);
            gl.Vertex(-10.0f, -10.0f, -10.0f);
            gl.Vertex(10.0f, -10.0f, -10.0f);
            gl.Vertex(10.0f, -10.0f, 10.0f);
            gl.Vertex(-10.0f, -10.0f, 10.0f);

            gl.Color(1.0, 0, 1);
            gl.Vertex(-10.0f, -10.0f, -10.0f);
            gl.Vertex(-10.0f, -10.0f, 10.0f);
            gl.Vertex(-10.0f, 10.0f, 10.0f);
            gl.Vertex(-10.0f, 10.0f, -10.0f);

            gl.Color(0, 1.0, 0);
            gl.Vertex(-10.0f, -10.0f, 10.0f);
            gl.Vertex(10.0f, -10.0f, 10.0f);
            gl.Vertex(10.0f, 10.0f, 10.0f);
            gl.Vertex(-10.0f, 10.0f, 10.0f);

            gl.Color(0, 0, 1.0);
            gl.Vertex(-10.0f, 10.0f, -10.0f);
            gl.Vertex(-10.0f, 10.0f, 10.0f);
            gl.Vertex(10.0f, 10.0f, 10.0f);
            gl.Vertex(10.0f, 10.0f, -10.0f);

            gl.Color(0, 1, 1.0);
            gl.Vertex(10.0f, -10.0f, -10.0f);
            gl.Vertex(10.0f, 10.0f, -10.0f);
            gl.Vertex(10.0f, 10.0f, 10.0f);
            gl.Vertex(10.0f, -10.0f, 10.0f);
            gl.End();
            gl.PopMatrix();
        }
        public void Initialized()
        {
            OpenGL gl = getGlInstance();
              gl.ClearColor(0, 0, 0, 0);
           gl.ShadeModel(OpenGL.GL_SMOOTH);                        // shading mathod: GL_SMOOTH or GL_FLAT
            gl.PixelStore(OpenGL.GL_UNPACK_ALIGNMENT, 4);          // 4-byte pixel alignment

            // enable/disable features
            gl.Hint(OpenGL.GL_PERSPECTIVE_CORRECTION_HINT, OpenGL.GL_NICEST);
            //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
            //glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
            gl.Enable(OpenGL.GL_DEPTH_TEST);
            gl.Enable(OpenGL.GL_LIGHTING);
            gl.Enable(OpenGL.GL_TEXTURE_2D);
            gl.Enable(OpenGL.GL_CULL_FACE);
            gl.Enable(OpenGL.GL_BLEND);
            gl.Enable(OpenGL.GL_SCISSOR_TEST);

            // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
            gl.ColorMaterial(OpenGL.GL_FRONT_AND_BACK, OpenGL.GL_AMBIENT_AND_DIFFUSE);
            gl.Enable(OpenGL.GL_COLOR_MATERIAL);

            gl.ClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);    // background color
            gl.ClearStencil(0);                              // clear stencil buffer
            gl.ClearDepth(1.0);                             // 0 is near, 1 is far
            gl.DepthFunc(OpenGL.GL_LEQUAL);




            //initLights();                                   /* 初始化OpenGL灯光 */
            float[] lightKa = { 1.0f, 1.0f, 1.0f, 0.0f };      // 环境光，基本亮度，可以认为是太阳光
            float[] lightKd = { 1.0f, 1.0f, 1.0f, 0.0f };      // diffuse light
            float[] lightKs = { 1f,1f,1f,1f};               // specular light
            gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_AMBIENT, lightKa);
            gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_DIFFUSE, lightKd);
           // gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_SPECULAR, lightKs);

            // position the light in eye space
            float[] lightPos = { 16f, 9f, -18f, 0f };               // directional light
            gl.Light(OpenGL.GL_LIGHT0, OpenGL.GL_POSITION, lightPos);
            gl.LightModel(OpenGL.GL_FRONT, OpenGL.GL_AMBIENT_AND_DIFFUSE);
            gl.Enable(OpenGL.GL_LIGHT0);                            // MUST enable each light source after configuration

           // gl.PolygonMode(OpenGL.GL_FRONT_AND_BACK, OpenGL.GL_FILL);
           // gl.Enable(OpenGL.GL_DEPTH_TEST);
           // gl.Enable(OpenGL.GL_CULL_FACE);
            gl.Enable(OpenGL.GL_NORMALIZE);
            

        }

       private double[] identity()
        {
            double[] m = new double[16];
            m[0] = m[5] = m[10] = m[15] = 1.0;
            m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0;
            return m;
        }
        private double[] getTranspose(double[] m)
        {
            double[] tm = new double[16];
            tm[0] = m[0]; tm[1] = m[4]; tm[2] = m[8]; tm[3] = m[12];
            tm[4] = m[1]; tm[5] = m[5]; tm[6] = m[9]; tm[7] = m[13];
            tm[8] = m[2]; tm[9] = m[6]; tm[10] = m[10]; tm[11] = m[14];
            tm[12] = m[3]; tm[13] = m[7]; tm[14] = m[11]; tm[15] = m[15];
            return tm;
        }
        public void drawGrid(float size, float step)
        {
            OpenGL gl = glInstance;
            // disable lighting
            gl.Disable(OpenGL.GL_LIGHTING);

            gl.Begin(OpenGL.GL_LINES);

            gl.Color(0.3f, 0.3f, 0.3f);
            for (float i = step; i <= size; i += step)
            {
                gl.Vertex(-size, 0, i);   // lines parallel to X-axis
                gl.Vertex(size, 0, i);
                gl.Vertex(-size, 0, -i);   // lines parallel to X-axis
                gl.Vertex(size, 0, -i);

                gl.Vertex(i, 0, -size);   // lines parallel to Z-axis
                gl.Vertex(i, 0, size);
                gl.Vertex(-i, 0, -size);   // lines parallel to Z-axis
                gl.Vertex(-i, 0, size);
            }

            // x-axis
            gl.Color(0.5f, 0, 0);
            gl.Vertex(-size, 0, 0);
            gl.Vertex(size, 0, 0);

            // z-axis
            gl.Color(0, 0, 0.5f);
            gl.Vertex(0, 0, -size);
            gl.Vertex(0, 0, size);

            gl.End();

            // enable lighting back
            gl.Enable(OpenGL.GL_LIGHTING);
        }
        public void setViewportSub(int x, int y, int width, int height, float nearPlane, float farPlane)
        {
            OpenGL gl = glInstance;
            // set viewport
            gl.Viewport(x, y, width, height);
            gl.Scissor(x, y, width, height);

            // set perspective viewing frustum
            setFrustum(FOV_Y, (float)(width) / height, nearPlane, farPlane); // FOV, AspectRatio, NearClip, FarClip
            // copy projection matrix to OpenGL
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.LoadMatrix(getTranspose(matrixProjection));
            gl.MatrixMode(OpenGL.GL_MODELVIEW);
            gl.LoadIdentity();

        }

       public  void setFrustum(float l, float r, float b, float t, float n, float f)
        {
            matrixProjection = identity();
            matrixProjection[0] = 2 * n / (r - l);
            matrixProjection[2] = (r + l) / (r - l);
            matrixProjection[5] = 2 * n / (t - b);
            matrixProjection[6] = (t + b) / (t - b);
            matrixProjection[10] = -(f + n) / (f - n);
            matrixProjection[11] = -(2 * f * n) / (f - n);
            matrixProjection[14] = -1;
            matrixProjection[15] = 0;
        }
        public void setFrustum(float fovY, float aspectRatio, float front, float back)
        {
            OpenGL gl = glInstance;
            float tangent = (float)Math.Tan(fovY / 2 * DEG2RAD);   // tangent of half fovY
            float height = front * tangent;           // half height of near plane
            float width = height * aspectRatio;       // half width of near plane

            // params: left, right, bottom, top, near, far
            setFrustum(-width, width, -height, height, front, back);
        }

        public void rotateCamera(int x, int y)
        {
            cameraAngleY += (x - mouseX);
            cameraAngleX += (y - mouseY);
            setMousePos(x, y);
            
        }

        public void moveCameraXY(int x, int y)
        {
            cameraPosition[0] += (x - mouseX) * 0.1f;
            cameraPosition[1] += (y - mouseY) * -0.1f;
            setMousePos(x, y);
            Debug.WriteLine(cameraPosition[0] + " " + cameraPosition[1] + " " + cameraPosition[2] + " ");
        }
        public void moveCameraZ(int x, int y)
        {
            //cameraPosition[1] += (x - mouseX);
            cameraPosition[2] += (y - mouseY) * 0.1f;
            setMousePos(x, y);
        }

        public void setMousePos(int x, int y)
        {
            mouseX = x;
            mouseY = y;
        }
        public void zoomCamera(int y)
        {
            cameraDistance -= (y - mouseY) * 0.1f;
            mouseY = y;
        }
        public void zoomCameraDelta(int delta)
        {
            cameraDistance -= delta;
        }
        public void resetView()
        {
            cameraAngleX = CAMERA_ANGLE_X;
            cameraAngleY = CAMERA_ANGLE_Y;
            cameraHight = CAMERA_HIGHT;
            cameraDistance = CAMERA_DISTANCE;
            cameraPosition[0] = cameraPosition[1] = cameraPosition[2] = 0;
        }

        public int DrawFlag { get; set; }
    }
}

