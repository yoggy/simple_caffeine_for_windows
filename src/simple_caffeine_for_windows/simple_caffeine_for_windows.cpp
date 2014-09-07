#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdio.h>

void PreventSleep()
{
	printf("PreventSleep()\n");

	// ディスプレイをオフにするのを防ぐ
	// http://msdn.microsoft.com/ja-jp/library/cc429178.aspx

	::SetThreadExecutionState(ES_DISPLAY_REQUIRED);

	// shiftキーを押す操作を行い、スクリーンセーバーが起動するのを防ぐ
	// http://msdn.microsoft.com/ja-jp/library/cc411004.aspx

	INPUT input[2];
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wScan = ::MapVirtualKey(VK_SHIFT, 0);
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = ::GetMessageExtraInfo();
	input[0].ki.wVk = VK_SHIFT;
	input[0].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;

	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wScan = ::MapVirtualKey(VK_SHIFT, 0);
	input[1].ki.time = 0;
	input[1].ki.dwExtraInfo = ::GetMessageExtraInfo();
	input[1].ki.wVk = VK_SHIFT;
	input[1].ki.dwFlags = KEYEVENTF_EXTENDEDKEY |KEYEVENTF_KEYUP;
	
	::SendInput(2, input, sizeof(INPUT));
}

int main(int argc, char* argv[])
{
	while(true) {
		::Sleep(1000); // 1秒
		PreventSleep();
	}

	return 0;
}

