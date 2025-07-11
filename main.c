#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <gl/gl.h>

#define LMAX 16
#define CMAX 3
#define V_MAIOR 3.0f
#define V_MENOR 1.0f

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
double** criar_matriz();
void** liberar_matriz(void** m);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLS";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    hwnd = CreateWindowEx(0,
                          "GLS",
                          "Janela",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          720,
                          720,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    EnableOpenGL(hwnd, &hDC, &hRC);

    while (!bQuit)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            double **m = criar_matriz();
            double escalaTela = 0.15f;

            glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();
            glRotatef(theta, 0.0f, 1.0f, 0.0f);
            glScaled(escalaTela, escalaTela, escalaTela);


            glBegin(GL_POLYGON);

                glColor3d(m[0][0], m[0][1], m[0][2]);   glVertex2f(V_MENOR, V_MAIOR);
                glColor3d(m[1][0], m[1][1], m[1][2]);   glVertex2f(V_MAIOR, V_MENOR);
                glColor3d(m[2][0], m[2][1], m[2][2]);   glVertex2f(V_MAIOR, -V_MENOR);
                glColor3d(m[3][0], m[3][1], m[3][2]);   glVertex2f(-V_MAIOR, -V_MAIOR);
                glColor3d(m[4][0], m[4][1], m[4][2]);   glVertex2f(-V_MENOR, V_MAIOR);
                glColor3d(m[5][0], m[5][1], m[5][2]);   glVertex2f(-V_MAIOR, V_MAIOR);

            glEnd();

            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep (1);

            m = (double**) liberar_matriz((void**)m);
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);

    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

double** criar_matriz()
{
    srand(time(NULL));
    double **m = calloc(LMAX, sizeof(double*));
    register int i;
    register int j;
    double cor = 0.0f;

    for(i = 0; i < LMAX; i++)
        m[i] = calloc(CMAX, sizeof(double));

    for(i = 0; i < LMAX; i++){
        for(j = 0; j < CMAX; j++){
            cor = cor + 0.135f * (rand()%3);
            m[i][j] = cor;
            cor = cor + 0.27f * (rand()%3);
            m[i][j] = cor;
            cor = cor + 0.405f * (rand()%3);
            m[i][j] = cor;
            cor = 0.0f;
        }
    }

    return m;
}

void** liberar_matriz(void** m)
{
    register int i;

    for(i = 0; i < LMAX; i++){
        free(m[i]);
        m[i] = NULL;
    }

    free(m);

    return NULL;
}

