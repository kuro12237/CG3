#pragma once
#include"Pch.h"
#include"WinApp.h"
#include"LogManager.h"

class Input
{
public:


	static Input * GetInstance();

	static void Initialize();

	static void BeginFlame();

	bool PushKey(uint8_t keyNum);

	bool PushKeyPressed(uint32_t keyNum);

private:

	static void CreateKeybordDevice();

	ComPtr<IDirectInput8> directInput = nullptr;
	ComPtr<IDirectInputDevice8> keyboard = nullptr;

	BYTE keys[256] = {};
	BYTE preKeys[256] = {};

	bool isInitialize=false;

	//0x80=押している状態
	//0x00=押してない状態
	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;
};

