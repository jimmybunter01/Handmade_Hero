/*
	===========================================================
	$Creator: James $
	$Notice: (C) Copyright 2021 Wings of Rebellion, Inc. All Rights Reserved. $
	===========================================================
*/

#include <windows.h>

//Depeding on the context of when static is used it can mean different things. These macros are define to make it clear what that meaning is when reading the code. 
#define internal static //Used for functions which can only be called from the file they are in.
#define local_persist static  //Used for local variables which persist.
#define global_variable static  //Used for global variables.

// TODO (James): This is a global for now. Automatically set to 0/false as it is static.
global_variable bool Running;

LRESULT CALLBACK MainWindowCallback (HWND Window, 
									 UINT Message, 
									 WPARAM WParam, 
									 LPARAM LParam)
{
	LRESULT Result = 0;	
		
	switch(Message)
	{
		//Window Resizing
		case WM_SIZE:
		{
			OutputDebugString("WM_SZIE\n");
		} break;
				
		//'X' button is clicked on.
		case WM_CLOSE:
		{
			//TOdo (James): Handle this with a message to the user?
			Running = false;
		} break;
		
		case WM_ACTIVATEAPP:
		{
			OutputDebugString("WM_ACTIVEAPP\n");
		} break;
		
		case WM_DESTROY:
		{
			// TODO (James): Handle this error + recreate Window?
			Running = false;
		} break;
		
		case WM_PAINT:
		{
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window, &Paint);
			int X = Paint.rcPaint.left;
			int Y = Paint.rcPaint.top;
			int Width = Paint.rcPaint.right - Paint.rcPaint.left;
			int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			PatBlt(DeviceContext, X, Y, Width, Height, WHITENESS);
			EndPaint(Window, &Paint);
			
		} break;
		
		default:
		{ 
			OutputDebugString("WM_DEFAULT\n");
			Result = DefWindowProc(Window, Message, WParam, LParam);
		} break;
	}
	
	return(Result);
}

int CALLBACK WinMain(
    HINSTANCE   Instance,
    HINSTANCE   PrevInstance,
    LPSTR       CommandLine,
    int         ShowCode)
{
	WNDCLASS WindowClass = {}; 
	
	
	WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowCallback;
	WindowClass.hInstance = Instance; //Could use GetModuleHandle(0); instead to get the instance of the code that is runnnning.
	
	// WindowClass.hIcon = ; Will be used to include the icon associated with the window.
	
	WindowClass.lpszClassName = "HandmadeHeroWindowClass"; 
	
	//
	if(RegisterClass(&WindowClass))
	{ 
		HWND WindowHandle = CreateWindowEx(
			0,
			WindowClass.lpszClassName,
			"HandmadeHero",
			WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			Instance,
			0
		);
		if(WindowHandle)
		{	
			//For Loop without constraitns = like while loop.
			while(Running)
			{
				MSG Message;
				BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
				if(MessageResult > 0)
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
				{
					break;
				}
			}
			
		}
		else
		{
			//TODO (James): Logging
		}
	}
	else 
	{
		// TODO (James): Logging
	}
	
    return(0);
}