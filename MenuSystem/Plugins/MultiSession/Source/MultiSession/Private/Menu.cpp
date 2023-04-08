// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	//�������� �Է¸�� ���콺�� ����
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		//������ ���� ����ý��ۿ� �����ϴ� ���� ����ý��� get
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	//�޴� �����ϸ鼭 Ŀ���� ��������Ʈ�� �޴� Ŭ���� �ݹ��Լ� ���
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	//��ư�� �Լ� ����
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	if (SingleButton)
	{
		SingleButton->OnClicked.AddDynamic(this, &ThisClass::SingleButtonClicked);
	}
	return true;
}

//ServerTravel�Լ� ������ �ڵ� ȣ��
void UMenu::NativeDestruct()
{
	MenuTearDown();

	Super::NativeDestruct();
}

//��Ƽ�÷��� �������̽��� ���ǻ����õ���� ��������Ʈ�� ���� ����
void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString(TEXT("Session Created Successfuly"))
			);
		}
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/ThirdPerson/Maps/Lobby?listen");
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Session Created Failed"))
			);
		}
	}
}

void UMenu::HostButtonClicked()
{
	if (MultiplayerSessionSubsystem)
	{
		//�޴��������� host Ŭ���� ���� ����, ���ڴ� ���� �������Ʈ������ �Ѿ�� 
		MultiplayerSessionSubsystem->CreateSession(NumPublicConnections,MatchType);
		
	}
}

void UMenu::JoinButtonClicked()
{
}

void UMenu::SingleButtonClicked()
{
}

//servertravel�Լ� ������ �ڵ� ȣ��( �� �̵� ������ ���� �����ϰ� �Է¸�� �������� ��ȯ
void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
