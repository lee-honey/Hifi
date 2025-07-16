// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
#include "Stats/Stats.h"
#include "ABBeatManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnBeat)
/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABBeatManager : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const { return true; }
	virtual TStatId GetStatId() const override;

public:
	// beat setting function
	void SetBeatInitialize(const int32 InBPM, const float InOffset = 0.f);

public:
	// get - set function
	FORCEINLINE bool GetBeat() const { return Beat; }
	FORCEINLINE int32 GetBPM() const { return BPM; }
	FORCEINLINE bool GetIsOffset() const { return IsOffset; }
	FORCEINLINE float GetOffset() const { return Offset; }
	FORCEINLINE bool GetPerfect() const { return Perfect; }
	FORCEINLINE bool GetPerfectHalfBeat() const { return PerfectHalfBeat; }
	FORCEINLINE bool GetJudge() const { return Judge; }
	FORCEINLINE bool GetOneFour() const { return OneFour[0]; }
	FORCEINLINE bool GetTwoFour() const { return TwoFour[0]; }
	FORCEINLINE bool GetThreeFour() const { return ThreeFour[0]; }

	FORCEINLINE void SetPerfect(const bool InCheck) { Perfect = InCheck; }
	FORCEINLINE void SetJudge(const bool InCheck) { Judge = InCheck; }

public:
	// delegate
	FOnBeat OnBeat;

private:
	float BeatTime = 0.f;				// ��Ʈ�ð� ���
	float AccTime = 0.f;				// �����ð� (��Ʈ �߻����� ����)
	int32 BPM = 0;						// �д� ��Ʈ��
	float Offset = 0.f;					// ���� ���� �������� Offset
	bool IsOffset = true;				// Offset����
	bool Beat = false;					// �Ϲ� ��Ʈ �Է�			
	bool Perfect = false;
	bool PerfectHalfBeat = false;
	bool Judge = false;
	// ��Ʈ ���� �迭
	bool OneFour[2] = { false };
	bool TwoFour[2] = { false };
	bool ThreeFour[2] = { false };

	bool CanParring = false;
};
