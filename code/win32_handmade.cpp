#include <windows.h>

LRESULT CALLBACK MainWindowCallback( HWND   Window,
                                     UINT   Message,
                                     WPARAM WParam,
                                     LPARAM LParam)
{
    LRESULT Result = 0;
    switch(Message){
        case WM_SIZE:
        {
            OutputDebugStringA("WN_SIZE \n" );
            
        }break;
        case WM_DESTROY:
        {
            OutputDebugStringA("WN_DESTROY \n" );
            

        }break;
        case WM_CLOSE:
        {
            OutputDebugStringA("WN_CLOSE \n" );

        }break;
        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("WM_ACTIVATEAPP \n" );
        }break;
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext =  BeginPaint(Window,&Paint );

            int X = Paint.rcPaint.left;
            int Y = Paint.rcPaint.top;
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            int Width = Paint.rcPaint.right - Paint.rcPaint.left;
            static DWORD operation = WHITENESS;
            PatBlt(DeviceContext,X, Y, Width,Height, operation);
            if(operation == WHITENESS){
                operation  = BLACKNESS;
            }
            else{
                operation = WHITENESS;
            }

            EndPaint(Window, &Paint);
            
        }
        default:
        {
             //OutputDebugStringA("Default  \n" );
            Result = DefWindowProc(Window,Message,WParam,LParam); 
        }break;
        
    }


    return Result;
    
}

int CALLBACK WinMain(HINSTANCE Instance,
             HINSTANCE PrevInstance,
             LPSTR     CommandLine,
             int       ShowCode)
{
    WNDCLASS WindowsClass = {};
    WindowsClass.style=CS_OWNDC |CS_HREDRAW| CS_VREDRAW;
    WindowsClass.lpfnWndProc= MainWindowCallback;
    WindowsClass.hInstance= Instance;
    // WindowsClass.hIcon=;
    WindowsClass.lpszClassName="HandmadeHeroWindowClass";

    if((RegisterClass(&WindowsClass)))
    {
        HWND WindowHandle = CreateWindowEx(0,
                                           WindowsClass.lpszClassName ,
                                           "Handmade Hero",
                                           WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                           CW_USEDEFAULT,
                                           CW_USEDEFAULT,
                                           CW_USEDEFAULT,
                                           CW_USEDEFAULT,
                                           0,
                                           0,
                                           Instance,
                                           0);
        if(WindowHandle)
        {
            
            MSG Message;
            for(;;){
                BOOL MessageResult =  GetMessage(&Message,0,0,0);
                if(MessageResult > 0){
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                else{

                    break;

                }
            }
                
        }
        else{
        //TODO create a debug properly class
        }
    }
    else{
        //TODO create a debug properly class
    }
         
  return(0);
}

