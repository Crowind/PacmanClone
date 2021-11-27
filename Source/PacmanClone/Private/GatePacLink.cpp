// Fill out your copyright notice in the Description page of Project Settings.


#include "GatePacLink.h"

void AGatePacLink::Close()
{
	
	auto Node1 = Cast<APacNode>(Head1);

	if(Node1->UpLink!=nullptr && Node1->UpLink == this)
	{
		Head1Direction = Up;
		Node1->UpLink=nullptr;
	}
	if(Node1->BottomLink!=nullptr && Node1->BottomLink == this)
	{
		Node1->BottomLink=nullptr;
		Head1Direction = Down;
	}
	if(Node1->RightLink!=nullptr && Node1->RightLink == this)
	{
		Node1->RightLink=nullptr;
		Head1Direction = Right;
	}
	if(Node1->LeftLink!=nullptr && Node1->LeftLink == this)
	{
		Node1->LeftLink=nullptr;
		Head1Direction = Left;
	}
	auto Node2 = Cast<APacNode>(Head2);

	if(Node2->UpLink!=nullptr && Node2->UpLink == this)
	{
		Node2->UpLink=nullptr;
		Head1Direction = Up;
	}
	if(Node2->BottomLink!=nullptr && Node2->BottomLink == this)
	{
		Node2->BottomLink=nullptr;
		Head1Direction = Down;
	}
	if(Node2->RightLink!=nullptr && Node2->RightLink == this)
	{
		Node2->RightLink=nullptr;
		Head1Direction = Right;
	}
	if(Node2->LeftLink!=nullptr && Node2->LeftLink == this)
	{
		Node2->LeftLink=nullptr;
		Head1Direction = Left;
	}
}

void AGatePacLink::Open()
{
		const auto Node1 = Cast<APacNode>(Head1);
    	switch(Head1Direction.GetValue())
    	{
    	case Down:
    		{
    			Node1->BottomLink=this;
    			break;
    		}
    	case Right:
    		{
    			Node1->RightLink=this;
    			break;
    		}
    	case Up:
    		{
    			Node1->LeftLink=this;
    			break;
    		}
    	case Left:
    		{
    			Node1->LeftLink=this;
    			break;
    		}
    	default: ;
    	}
    	
	const auto Node2 = Cast<APacNode>(Head2);
	switch(Head1Direction.GetValue())
	{
	case Down:
		{
			Node2->BottomLink=this;
			break;
		}
	case Right:
		{
			Node2->RightLink=this;
			break;
		}
	case Up:
		{
			Node2->LeftLink=this;
			break;
		}
	case Left:
		{
			Node2->LeftLink=this;
			break;
		}
	default: ;
	}
	
}

void AGatePacLink::BeginPlay()
{
	Super::BeginPlay();
	Close();
}

void AGatePacLink::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(DotsCount==DotsThreshold)
	{
		Open();
	}
}
