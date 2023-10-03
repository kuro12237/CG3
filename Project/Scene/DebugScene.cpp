#include "DebugScene.h"

DebugScene::~DebugScene()
{
	Audio::SoundUnLoad(soundHandle_);	
}

void DebugScene::Initialize(GameManager* Scene)
{
	viewProjection.Initialize({ 0.2f,-0.6f,0.0f }, { 11.0f,5.0f,-15 });
	soundHandle_ = Audio::SoundLoadWave("Resources/Select.wav");
	Scene;
	
	sprite_ = make_unique<Sprite>();

	SpriteTexHandle = TextureManager::LoadTexture("Resources/uvChecker.png");
	sprite_->SetTexHandle(SpriteTexHandle);
	sprite_->Initialize(new SpriteBoxState,{0,0},{320,320});

	spriteWorldTransform_.Initialize();
}

void DebugScene::Update(GameManager* Scene)
{
	ImGui::Begin("MainCamera");
	ImGui::SliderFloat3("trans", &viewProjection.translation_.x, -15, 15);
	ImGui::SliderFloat3("rotate", &viewProjection.rotation_.x, -1, 1);
	ImGui::End();

	ImGui::Begin("key");
	ImGui::Text("0 Pushkey PlayAudio");
	ImGui::Text("9 Pushkey StateChange");
	ImGui::End();

	ImGui::Begin("Sprite");
	ImGui::ColorPicker4("color", &color.x);
	
	ImGui::Checkbox("NONE", &NoneFlag);
	ImGui::Checkbox("Add", &AddFlag);
	ImGui::Checkbox("Subtract", &SubtractFlag);
	ImGui::Checkbox("Multiply", &MultiplyFlag);
	ImGui::Checkbox("Screen", &ScreenFlag);
	ImGui::End();
#pragma region 
	if (NoneFlag)
	{
		sprite_->SetBlendMode(BlendNone);
		AddFlag = false;
		SubtractFlag = false;
		MultiplyFlag = false;
		ScreenFlag = false;
	}
	if (AddFlag)
	{
		sprite_->SetBlendMode(BlendAdd);
		NoneFlag = false;
		SubtractFlag = false;
		MultiplyFlag = false;
		ScreenFlag = false;
	}
	if (SubtractFlag)
	{
		sprite_->SetBlendMode(BlendSubtruct);
		AddFlag = false;
		NoneFlag = false;
		MultiplyFlag = false;
		ScreenFlag = false;
	}
	if (MultiplyFlag)
	{
		sprite_->SetBlendMode(BlendMultiply);
		AddFlag = false;
		SubtractFlag = false;
		NoneFlag = false;
		ScreenFlag = false;
	}
	if (ScreenFlag)
	{
		sprite_->SetBlendMode(BlendScreen);
		AddFlag = false;
		SubtractFlag = false;
		MultiplyFlag = false;
		NoneFlag=false;
	}

#pragma endregion

	sprite_->SetColor(color);

	if (Input::GetInstance()->PushKeyPressed(DIK_9))
	{
		Scene->ChangeState(new GameScene);
		return;
	}
	if (Input::GetInstance()->PushKeyPressed(DIK_0))
	{
		Audio::AudioPlayWave(soundHandle_);
	}
	
	spriteWorldTransform_.UpdateMatrix();

	viewProjection.UpdateMatrix();
	viewProjection = DebugTools::ConvertViewProjection(viewProjection);
}

void DebugScene::Draw(GameManager* Scene)
{

	sprite_->Draw(spriteWorldTransform_);

	Scene;
}


