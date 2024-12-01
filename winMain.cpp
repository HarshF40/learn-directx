//flow
//--> define a windows procedure (custom)
//--> define the entry point (int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow))
//--> register a class (window) using RegisterClassEx(&wc)
//--> create a instance of the window using CreateWindowEx() which will return a handle
//--> call the showWindow() to show the window
//--> run a message loop to keep running the window
//--> add the messsages










//int main() {
//	return 0;
//} this gives an error as this is not the entry point function for the windows application
//instead we do this

#include<Windows.h> //required to develop apps in windows (no shit)
#include"WindowsMessageMap.h"

//hInstance: Pointers to structure that hold information about our program
//hPrevInstance: this always NULL
//lpCmdLine: this will contain the extra command lines arguements which is passed from the command line
//nCmdShow: indication to the program to that how the window should be shown
//CALLBACK: modifier for a function --> tells c++ to use different calling convention (use stdcall)

//defining a custom windows procedure
//LRESULT is a 32 bit unsigned integer
//CALLBACK is a macro here which extends to _stdcall... this a convention to call a function when interacting windows OS
//LPARAM AND WPARAM: integer values depends upon the msg
//LPSTR --> long pointer to string of characters
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static WindowsMessageMap mm;
	OutputDebugStringA( mm(msg, lParam, wParam).c_str() );

	switch (msg) {
	case WM_CLOSE : PostQuitMessage(69);
					break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {

	//register window class
	//this function takes a WNDCLASSEX structure --> all paraameters in one struct
	const auto pClassName = L"First Project"; //wide character string
	WNDCLASSEX wc = { 0 }; //this will have all the parameters grouped to pass into the function RegisterClassEx()

	//typedef struct tagWNDCLASSEXA {
	//	UINT      cbSize;			//size of the structure
	//	UINT      style;			//class styles --> bit flags
	//	WNDPROC   lpfnWndProc;		//long pointer to function window proc : pointer to a function which will handle all the messages for the windoww **important
	//	int       cbClsExtra;		//allows us to allocate some extra bytes in the class to store custom data
	//	int       cbWndExtra;		allows us to allocate extra byte of data for every instance of the window
	//	HINSTANCE hInstance;
	//	HICON     hIcon;			//custom icon
	//	HCURSOR   hCursor;			//custom cursor
	//	HBRUSH    hbrBackground;	//to draw the background of the windows
	//	LPCSTR    lpszMenuName;		//
	//	LPCSTR    lpszClassName;	//name we use when we create a window of the class type
	//	HICON     hIconSm;			//custom icom for our application
	//} WNDCLASSEXA, * PWNDCLASSEXA, * NPWNDCLASSEXA, * LPWNDCLASSEXA

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = CreateSolidBrush(RGB(0,0,0));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;

	//to register the window
	RegisterClassEx(&wc);

	//creating window instance
	HWND hWnd = CreateWindowEx( //this will used to do operation to later on the window
		0, //exstyle
		pClassName, //class name
		L"DirectX", //name of the window
		WS_OVERLAPPEDWINDOW, //styles or the different functionality of the classes
		200,200, //position of the window (X,Y)
		640,480, //width and height of the window
		nullptr, //handle to the parent
		nullptr, //handle to the menu
		hInstance,
		nullptr //message which is sent to the created window by this funtion before it returns
		);
	//to show the window (ohhhh god please now)
	//2 parameters window handle and nCmdShow: controls how the widows to be showned
	ShowWindow(hWnd, SW_SHOW); //SW_SHOW is an enum and it controls how the window is to be shown

	// Message loop (messages are inuts or proccess)
	MSG msg = { 0 }; //holds the message
	//MSG is a structured defined that contains the information about the message , including the window handle, message ID, parameters, etc.
	BOOL getMsg;
	while (getMsg = GetMessage(&msg, nullptr, 0, 0)) { //GetMessage retrieves the message from the queue
		//&msg : pointer to the MSG structure that will hold the retrieved messages
		//nullptr takes the pointer to the handle (nullptr for all the windows)
		//0,0 range to look for the messgaes 0,0 for all the messages
		TranslateMessage(&msg); //translates keyboard messages
		DispatchMessage(&msg); //dispatches the msg to the window procedure
	}
	if (getMsg == -1) {
		return -1;
	}
	return static_cast<int>(msg.wParam); //returns 69
}