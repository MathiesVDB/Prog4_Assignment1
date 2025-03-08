#pragma once

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

//------------------------------------------------
// Current Commands
//------------------------------------------------

class MoveLeftCommand : public Command
{
public:
	void Execute() override;
};

class MoveRightCommand : public Command
{
public:
	void Execute() override;
};

class MoveUpCommand : public Command
{
public:
	void Execute() override;
};

class MoveDownCommand : public Command
{
public:
	void Execute() override;
};