// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTISESSION_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//���� �������Ʈ���� ȣ��
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections=2, FString TypeOfMatch=FString(TEXT("Free")));
protected:
	virtual bool Initialize() override;
	//���� ���� ������ �ڵ�����
	virtual void NativeDestruct() override;

	//��Ƽ�÷��� ����ý��� Ŀ���� ��������Ʈ�� ���� �ݹ��Լ�
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);

private:
	//�������Ʈ ���� ��ư ���ε� (meta�� �����Ұ�� �������Ʈ�̸��� �ݵ�� ���ƾ���
	UPROPERTY(meta=(BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* SingleButton;

	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();
	UFUNCTION()
	void SingleButtonClicked();

	void MenuTearDown();
	//�¶��� ���Ǳ�� ó�� �ϰ� ����� �ý���
	class UMultiplayerSessionsSubsystem* MultiplayerSessionSubsystem;

	int32 NumPublicConnections{ 2 };
	FString MatchType{TEXT("Free")};
};
