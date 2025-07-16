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
    // BPM�� �ʴ� ��Ʈ���� ��ȯ�ؼ� ��Ʈ ���ӽð� ���
    BeatTime = 1.f / (static_cast<float>(BPM) / 60.f);
    AccTime = 0.f;

    // Init���� �־��� Offset�� ������ true
    if (Offset != 0.f)
    {
        IsOffset = true;
    }
    else
    {
        IsOffset = false;
    }

    // ��Ʈ ���� �ʱ�ȭ
    // -> Ư�� ��Ʈ�� �߻��ߴ��� ���θ� �����ϴµ� ���
	OneFour[0] = false;
	TwoFour[0] = false;
	ThreeFour[0] = false;
	OneFour[1] = false;
	TwoFour[1] = false;
	ThreeFour[1] = false;

    // ���� ���� �ʱ�ȭ
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
    // OffsetȰ��ȭ�� ���
    if (IsOffset)
    {
        // �����ð� ������
        if (AccTime >= Offset)
        {
            // Offset ��Ȱ��ȭ�ϰ� �����ð����� Offset�� ���� �� ��Ʈ ���� �ʱ�ȭ
			IsOffset = false;
			AccTime = AccTime - Offset;

			OneFour[1] = false;
			TwoFour[1] = false;
			ThreeFour[1] = false;
        }
    }
    // �̰� �ᱹ 4���� 4��Ʈ ó��
    else if (AccTime >= BeatTime)
    {
        AccTime = AccTime - BeatTime;
        // ��Ʈ�߻�!
		Beat = true;
		OneFour[1] = false;          // ������
		TwoFour[1] = false;          // ������
		ThreeFour[1] = false;        // ������   
		CanParring = true;
    }
    // Offset���� ���� ��� Beat ����
    else
    {
        // ��Ʈ������ ���缭 ���� ����
        Beat = false;
        CanParring = false;
        // 4���� 1��Ʈ ���� üũ
        // �����ð� �Ѿ��� 4����1��Ʈ�� �������� �ƴ϶�� ����
        if (AccTime >= BeatTime * 0.25f && !OneFour[1])
        {
			OneFour[1] = true;       // ���� ������
			OneFour[0] = true;       // ���� 4����1��Ʈ
			Perfect = false;         // ��Ȯ�� ���ڰ� �ƴ�
			PerfectHalfBeat = false;
			CanParring = true;

        }
        else
        {
            // 4���� 1��Ʈ�� �̹� ��������
            // = ���� 4���� 1��Ʈ�� �ƴ�
            OneFour[0] = false;
            CanParring = false;
        }
        // 4���� 2��Ʈ ���� üũ
        // �����ð� �Ѿ��� 4����2��Ʈ�� �������� �ƴ϶�� ����
        if (AccTime >= BeatTime * 0.5f && !TwoFour[1])
        {
            TwoFour[1] = true;       // ���� ������
            TwoFour[0] = true;       // ���� 4���� 2��Ʈ
            CanParring = true;
        }
        else
        {
            // 4���� 2��Ʈ�� �̹� ��������
            // = ���� 4���� 2��Ʈ�� �ƴ�
            TwoFour[0] = false;
            CanParring = false;
        }
        // 4���� 3��Ʈ ���� üũ
        // �����ð� �Ѿ��� 4����3��Ʈ�� �������� �ƴ϶�� ����
        if (AccTime >= BeatTime * 0.75f && !ThreeFour[1])
        {
            PerfectHalfBeat = true;
            ThreeFour[1] = true;
            ThreeFour[0] = true;
            Perfect = true;          // ���� ���Ͽ�
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
