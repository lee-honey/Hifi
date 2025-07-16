// Fill out your copyright notice in the Description page of Project Settings.


#include "Beat/ABBeatManager.h"

void UABBeatManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UABBeatManager::SetBeatInitialize(const int32 InBPM, const float InOffset)
{
    BPM = InBPM;
    Offset = InOffset;
    // BPM을 초당 비트수로 변환해서 비트 지속시간 계산
    BeatTime = 1.f / (static_cast<float>(BPM) / 60.f);
    AccTime = 0.f;

    // Init에서 넣어준 Offset이 있으면 true
    if (Offset != 0.f)
    {
        IsOffset = true;
    }
    else
    {
        IsOffset = false;
    }

    // 비트 상태 초기화
    // -> 특정 비트가 발생했는지 여부를 추적하는데 사용
	OneFour[0] = false;
	TwoFour[0] = false;
	ThreeFour[0] = false;
	OneFour[1] = false;
	TwoFour[1] = false;
	ThreeFour[1] = false;

    // 상태 변수 초기화
	Perfect = false;
	PerfectHalfBeat = false;
	Beat = false;
}

void UABBeatManager::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Beat Manager Deinitialize"));
}

void UABBeatManager::Tick(float DeltaTime)
{
    AccTime += DeltaTime;
    // Offset활성화인 경우
    if (IsOffset)
    {
        // 누적시간 넘으면
        if (AccTime >= Offset)
        {
            // Offset 비활성화하고 누적시간에서 Offset값 빼준 뒤 비트 상태 초기화
			IsOffset = false;
			AccTime = AccTime - Offset;

			OneFour[1] = false;
			TwoFour[1] = false;
			ThreeFour[1] = false;
        }
    }
    // 이게 결국 4분의 4비트 처리
    else if (AccTime >= BeatTime)
    {
        AccTime = AccTime - BeatTime;
        // 비트발생!
		Beat = true;
		OneFour[1] = false;          // 지나감
		TwoFour[1] = false;          // 지나감
		ThreeFour[1] = false;        // 지나감   
		CanParring = true;
    }
    // Offset값이 없는 경우 Beat 설정
    else
    {
        // 비트구간에 맞춰서 상태 변경
        Beat = false;
        CanParring = false;
        // 4분의 1비트 구간 체크
        // 누적시간 넘었고 4분의1비트를 지나간게 아니라면 들어옴
        if (AccTime >= BeatTime * 0.25f && !OneFour[1])
        {
			OneFour[1] = true;       // 이제 지나감
			OneFour[0] = true;       // 현재 4분의1비트
			Perfect = false;         // 정확한 박자가 아님
			PerfectHalfBeat = false;
			CanParring = true;

        }
        else
        {
            // 4분의 1비트를 이미 지나갔음
            // = 현재 4분의 1비트가 아님
            OneFour[0] = false;
            CanParring = false;
        }
        // 4분의 2비트 구간 체크
        // 누적시간 넘었고 4분의2비트를 지나간게 아니라면 들어옴
        if (AccTime >= BeatTime * 0.5f && !TwoFour[1])
        {
            TwoFour[1] = true;       // 이제 지나감
            TwoFour[0] = true;       // 현재 4분의 2비트
            CanParring = true;
        }
        else
        {
            // 4분의 2비트를 이미 지나갔음
            // = 현재 4분의 2비트가 아님
            TwoFour[0] = false;
            CanParring = false;
        }
        // 4분의 3비트 구간 체크
        // 누적시간 넘었고 4분의3비트를 지나간게 아니라면 들어옴
        if (AccTime >= BeatTime * 0.75f && !ThreeFour[1])
        {
            PerfectHalfBeat = true;
            ThreeFour[1] = true;
            ThreeFour[0] = true;
            Perfect = true;          // 정박 축하요
            CanParring = true;
        }
        else
        {
            ThreeFour[0] = false;
            CanParring = false;
        }
    }
}

TStatId UABBeatManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UABBeatManager, STATGROUP_Tickables);
}
