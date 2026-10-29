#pragma once

#include<iostream>
#include<iomanip>
#include<conio.h>
#include<cassert>

#include"Func.h"
#include"List.h"
#include"Array.h"
#include"String.h"

using namespace std;

#define L_TYPES 3
#define D_TYPES 3

int d4()
{
	return rand() % 4 + 1;
}
int d6()
{
	return rand() % 6 + 1;
}
int d8()
{
	return rand() % 8 + 1;
}
int d10()
{
	return rand() % 10 + 1;
}
int d12()
{
	return rand() % 12 + 1;
}
int d20()
{
	return rand() % 20 + 1;
}

class Warrior;

class Skill
{
public:
	virtual ~Skill() = default;
	virtual void execute(Warrior* me, Warrior* w, Warrior* you = nullptr) = 0;
};

class SecondWind : public Skill
{
public:
	virtual void execute(Warrior* me, Warrior* w, Warrior* you) override;
};
class CureWounds : public Skill
{
public:
	virtual void execute(Warrior* me, Warrior* w, Warrior* you) override;
};
class MagicMissile : public Skill
{
public:
	virtual void execute(Warrior* me, Warrior* w, Warrior* you) override;
};
class AggressiveCharge : public Skill
{
public:
	virtual void execute(Warrior* me, Warrior* w, Warrior* you) override;
};
class BoneVolley : public Skill
{
public:
	virtual void execute(Warrior* me, Warrior* w, Warrior* you) override;
};
class UndeadFortitude : public Skill
{
public:
	virtual void execute(Warrior* me, Warrior* w, Warrior* you) override;
};

class Light;

class Warrior
{
	int HP;
	int maxHP;
	int (*roll)();
	int bonus;
	String type;

protected:
	//List<Skill*> skills;
	Skill* skill;
	bool skillUsed = false;

public:
	Warrior(int HP, int (*roll)(), int bonus, Skill* skill = nullptr, String type = "")
	{
		this->HP = maxHP = HP;
		this->roll = roll;
		this->bonus = bonus;
		this->skill = skill;
		this->type = type;
	}
	Warrior(int lvl, int baseHP, int increase, int (*roll)(), int bonus, Skill* skill = nullptr, String type = "")
	{
		this->HP = maxHP = baseHP + (increase * (lvl - 1));
		this->roll = roll;
		this->bonus = bonus;
		this->skill = skill;
		this->type = type;
	}

	virtual ~Warrior()
	{
		if (skill)
		{
			delete skill;
		}
	}

	int getHP()        const { return HP; }
	int getMaxHP()     const { return maxHP; }
	int getDamage()    const { return roll() + bonus; }
	String getType()   const { return type; }
	Skill* getSkill()  const { return skill; }
	bool isSkillUsed() const { return skillUsed; }

	void setHP(int h)
	{
		assert(h >= 0 && h <= maxHP);
		HP = h;
	}

	void useSkill() { skillUsed = true; }
	void resetSkill() { skillUsed = false; }

	virtual void attack(Warrior* w, Array<Light*>* party = nullptr) = 0;
	virtual int getLevel() const { return 0; }

	friend ostream& operator<<(ostream& out, const Warrior* w);
	virtual ostream& print(ostream& out) const
	{
		out << " HP: " << setw(2) << right << setfill(' ') << HP << endl;
		return out;
	}
};

ostream& operator<<(ostream& out, const Warrior* w)
{
	out << setw(10) << left << setfill('.');
	return w->print(out);
}


void SecondWind::execute(Warrior* me, Warrior* w, Warrior* you)
{
	cout << "Cast Second Wind -> "; SetColor(Green, Black);
	cout << me->getType() << " (HP: " << me->getHP() << ")\n"; SetColor(White, Black);

	int oldHP = me->getHP(), newHP = oldHP + d10() + me->getLevel();
	if (newHP > me->getMaxHP()) { newHP = me->getMaxHP(); };
	me->setHP(newHP);

	cout << "Health restored: "; SetColor(LightGreen, Black);
	cout << "+" << newHP - oldHP << endl; SetColor(White, Black);
}
void CureWounds::execute(Warrior* me, Warrior* w, Warrior* you)
{
	cout << "Cast Cure Wounds -> "; SetColor(Green, Black);
	cout << you->getType() << " (HP: " << you->getHP() << ")\n"; SetColor(White, Black);

	int oldHP = you->getHP(), newHP = oldHP + d8() + me->getLevel();
	if (newHP > you->getMaxHP()) { newHP = you->getMaxHP(); };
	you->setHP(newHP);

	cout << "Health restored: "; SetColor(LightGreen, Black);
	cout << "+" << newHP - oldHP << endl; SetColor(White, Black);
}
void MagicMissile::execute(Warrior* me, Warrior* w, Warrior* you)
{
	cout << "Cast Magic Missile -> "; SetColor(LightBlue, Black);
	cout << w->getType() << " (HP: " << w->getHP() << ")\n"; SetColor(White, Black);

	int DMG = d4() + d4() + d4() + 3, hit = w->getHP() - DMG;
	(hit <= 0) ? w->setHP(0) : w->setHP(hit);

	cout << "Damage rolled: "; SetColor(LightRed, Black);
	cout << "-" << DMG << endl; SetColor(White, Black);
}
void AggressiveCharge::execute(Warrior* me, Warrior* w, Warrior* you)
{
	cout << "Aggressive Charge Called -> "; SetColor(Green, Black);
	cout << w->getType() << " (HP: " << w->getHP() << ")\n"; SetColor(White, Black);

	int DMG = d6(), hit = w->getHP() - DMG;
	(hit <= 0) ? w->setHP(0) : w->setHP(hit);

	cout << "Damage rolled: "; SetColor(LightRed, Black);
	cout << "-" << DMG << endl; SetColor(White, Black);
}
void BoneVolley::execute(Warrior* me, Warrior* w, Warrior* you)
{
	cout << "Bone Volley Called -> "; SetColor(Green, Black);
	cout << w->getType() << " (HP: " << w->getHP() << ")\n"; SetColor(White, Black);

	int DMG = d6() + d6(), hit = w->getHP() - DMG;
	(hit <= 0) ? w->setHP(0) : w->setHP(hit);

	cout << "Damage rolled: "; SetColor(LightRed, Black);
	cout << "-" << DMG << endl; SetColor(White, Black);
}
void UndeadFortitude::execute(Warrior* me, Warrior* w, Warrior* you)
{
	cout << "Undead Fortitude Called!\n";
	(d20() >= me->getHP() + 5) ? me->setHP(1) : me->setHP(0);
}


class Light : public Warrior
{
protected:
	int level = 1;

public:
	Light(int lvl, int baseHP, int increase, int(*roll)(), int bonus, Skill* skill, String type) : Warrior(lvl, baseHP, increase, roll, bonus, skill, type) { level = lvl; }

	virtual int getLevel() const final override { return level; }

	virtual ostream& print(ostream& out) const override
	{
		out << "LVL " << level << ".";
		return Warrior::print(out);
	}
};


class Dark : public Warrior
{
public:
	Dark(int HP, int(*roll)(), int bonus, Skill* skill, String type) : Warrior(HP, roll, bonus, skill, type) {}

	virtual ostream& print(ostream& out) const override
	{
		out << "      ";
		return Warrior::print(out);
	}
};


class Fighter : public Light
{
	const static int baseHP = 12;
	const static int increase = 8;
	const static int bonus = 3;

public:
	Fighter(int lvl, Skill* skill = nullptr, String type = "Fighter") : Light(lvl, baseHP, increase, d8, bonus, skill, type) {}

	virtual void attack(Warrior* w, Array<Light*>* party) override
	{
		SetColor(Green, Black); cout << "Fighter (HP: " << this->getHP() << ")"; SetColor(White, Black);
		cout << " is attacking "; SetColor(LightBlue, Black);
		cout << w->getType() << " (HP: " << w->getHP() << ")"; SetColor(White, Black);
		cout << " with a Longsword!\n";

		cout << "[A]ttack   [S]kill\n"; bool action = false;

		while (!action)
		{
			int key = _getch();
			if (key == 'a' || key == 'A')
			{
				int DMG = getDamage(), hit = w->getHP() - DMG;
				(hit <= 0) ? w->setHP(0) : w->setHP(hit);

				cout << "Damage rolled: "; SetColor(LightRed, Black);
				cout << "-" << DMG << endl; SetColor(White, Black);
				action = true;
			}
			else if (key == 's' || key == 'S')
			{
				if (skill && skillUsed == false)
				{
					if (getHP() < getMaxHP())
					{
						skill->execute(this, w);
						action = true;
						useSkill();
					}
					else
					{
						cout << "Fighter is at full health.\n";
					}
				}
				else
				{
					cout << "No skill availiable\n";
				}
			}
		}
	}

	virtual ostream& print(ostream& out) const override
	{
		out << "Fighter";
		return Light::print(out);
	}
};
class Ranger : public Light
{
	const static int baseHP = 12;
	const static int increase = 8;
	const static int bonus = 3;

public:
	Ranger(int lvl, Skill* skill = nullptr, String type = "Ranger") : Light(lvl, baseHP, increase, d8, bonus, skill, type) {}

	virtual void attack(Warrior* w, Array<Light*>* party) override
	{
		SetColor(Green, Black); cout << "Ranger (HP: " << this->getHP() << ")"; SetColor(White, Black);
		cout << " is attacking "; SetColor(LightBlue, Black);
		cout << w->getType() << " (HP: " << w->getHP() << ")"; SetColor(White, Black);
		cout << " with a Longbow!\n";

		cout << "[A]ttack   [S]kill\n"; bool action = false;

		while (!action)
		{
			int key = _getch();
			if (key == 'a' || key == 'A')
			{
				int DMG = getDamage(), hit = w->getHP() - DMG;
				(hit <= 0) ? w->setHP(0) : w->setHP(hit);

				cout << "Damage rolled: "; SetColor(LightRed, Black);
				cout << "-" << DMG << endl; SetColor(White, Black);
				action = true;
			}
			else if (key == 's' || key == 'S')
			{
				if (skill && skillUsed == false)
				{
					Array<Light*> injured;

					for (int i = 0; i < party->getSize(); ++i)
					{
						Light* member = (*party)[i];

						if (member->getHP() > 0 && member->getHP() < member->getMaxHP())
						{
							injured.add(member);
						}
					}

					if (injured.getSize() == 0)
					{
						cout << "No living allies need healing.\n";
					}
					else
					{
						Light* you = injured[rand() % injured.getSize()];
						skill->execute(this, w, you);
						useSkill();
						action = true;
					}
				}
				else
				{
					cout << "No skill availiable\n";
				}
			}
		}
	}

	virtual ostream& print(ostream& out) const override
	{
		out << "Ranger";
		return Light::print(out);
	}
};
class Wizard : public Light
{
	const static int baseHP = 8;
	const static int increase = 6;
	const static int bonus = 0;

public:
	Wizard(int lvl, Skill* skill = nullptr, String type = "Wizard") : Light(lvl, baseHP, increase, d10, bonus, skill, type) {}

	virtual void attack(Warrior* w, Array<Light*>* party) override
	{
		SetColor(Green, Black); cout << "Wizard (HP: " << this->getHP() << ")"; SetColor(White, Black);
		cout << " is attacking "; SetColor(LightBlue, Black);
		cout << w->getType() << " (HP: " << w->getHP() << ")"; SetColor(White, Black);
		cout << " with a Fire Bolt!\n";

		cout << "[A]ttack   [S]kill\n"; bool action = false;

		while (!action)
		{
			int key = _getch();
			if (key == 'a' || key == 'A')
			{
				int DMG = getDamage(), hit = w->getHP() - DMG;
				(hit <= 0) ? w->setHP(0) : w->setHP(hit);

				cout << "Damage rolled: "; SetColor(LightRed, Black);
				cout << "-" << DMG << endl; SetColor(White, Black);
				action = true;
			}
			else if (key == 's' || key == 'S')
			{
				if (skill && skillUsed == false)
				{
					skill->execute(this, w);
					action = true;
					useSkill();
				}
				else
				{
					cout << "No skill availiable\n";
				}
			}
		}
	}

	virtual ostream& print(ostream& out) const override
	{
		out << "Wizard";
		return Light::print(out);
	}
};


class Orc : public Dark
{
	const static int HP = 15;
	const static int bonus = 3;

public:
	Orc(Skill* skill = nullptr) : Dark(HP, d12, bonus, skill, "Orc") {}

	virtual void attack(Warrior* w, Array<Light*>* party) override
	{
		SetColor(LightBlue, Black); cout << "Orc (HP: " << this->getHP() << ")"; SetColor(White, Black);
		cout << " is attacking "; SetColor(Green, Black);
		cout << w->getType() << " (HP: " << w->getHP() << ")\n"; SetColor(White, Black);

		int DMG = getDamage(), hit = w->getHP() - DMG;
		(hit <= 0) ? w->setHP(0) : w->setHP(hit);

		cout << "Damage rolled: "; SetColor(LightRed, Black);
		cout << "-" << DMG << endl; SetColor(White, Black);

		if (skill && d20() > 12 && skillUsed == false && w->getHP() > 0)
		{
			skill->execute(this, w);
			useSkill();
		}
	}

	virtual ostream& print(ostream& out) const override
	{
		out << "Orc";
		return Dark::print(out);
	}
};
class Skeleton : public Dark
{
	const static int HP = 13;
	const static int bonus = 2;

public:
	Skeleton(Skill* skill = nullptr) : Dark(HP, d6, bonus, skill, "Skeleton") {}

	virtual void attack(Warrior* w, Array<Light*>* party) override
	{
		SetColor(LightBlue, Black); cout << "Skeleton (HP: " << this->getHP() << ")"; SetColor(White, Black);
		cout << " is attacking "; SetColor(Green, Black);
		cout << w->getType() << " (HP: " << w->getHP() << ")\n"; SetColor(White, Black);

		int DMG = getDamage(), hit = w->getHP() - DMG;
		(hit <= 0) ? w->setHP(0) : w->setHP(hit);

		cout << "Damage rolled: "; SetColor(LightRed, Black);
		cout << "-" << DMG << endl; SetColor(White, Black);

		if (skill && d20() > 12 && skillUsed == false && w->getHP() > 0)
		{
			skill->execute(this, w);
			useSkill();
		}
	}

	virtual ostream& print(ostream& out) const override
	{
		out << "Skeleton";
		return Dark::print(out);
	}
};
class Zombie : public Dark
{
	const static int HP = 22;
	const static int bonus = 1;

public:
	Zombie(Skill* skill = nullptr) : Dark(HP, d6, bonus, skill, "Zombie") {}

	virtual void attack(Warrior* w, Array<Light*>* party) override
	{
		SetColor(LightBlue, Black); cout << "Zombie (HP: " << this->getHP() << ")"; SetColor(White, Black);
		cout << " is attacking "; SetColor(Green, Black);
		cout << w->getType() << " (HP: " << w->getHP() << ")\n"; SetColor(White, Black);

		int DMG = getDamage(), hit = w->getHP() - DMG;
		(hit <= 0) ? w->setHP(0) : w->setHP(hit);

		cout << "Damage rolled: "; SetColor(LightRed, Black);
		cout << "-" << DMG << endl; SetColor(White, Black);
	}

	virtual ostream& print(ostream& out) const override
	{
		out << "Zombie";
		return Dark::print(out);
	}
};

class Battle
{
	List<Light*> lights;
	List<Dark*>  darks;

	int line = 0;

public:
	Battle(int party_size, int opponents)
	{
		Light* l = nullptr;
		for (int i = 0; i < party_size; i++)
		{
			int rnd = rand() % L_TYPES;
			switch (rnd)
			{
			case 0: l = new Fighter(1, new SecondWind); break;
			case 1: l = new Ranger(1, new CureWounds); break;
			case 2: l = new Wizard(1, new MagicMissile);
			}
			lights.push_back(l);
		}

		Dark* d = nullptr;
		for (int i = 0; i < opponents; i++)
		{
			int rnd = rand() % D_TYPES;
			switch (rnd)
			{
			case 0: d = new Orc(new AggressiveCharge); break;
			case 1: d = new Skeleton(new BoneVolley); break;
			case 2: d = new Zombie(new UndeadFortitude);
			}
			darks.push_back(d);
		}

		(party_size >= opponents) ? line = party_size : line = opponents;
	}

	~Battle()
	{
		for (int i = 0; i < lights.getSize(); i++)
		{
			delete lights[i];
		}

		for (int i = 0; i < darks.getSize(); i++)
		{
			delete darks[i];
		}
	}

	void print() const
	{
		SetColor(LightGreen, Black);
		cout << "------   LIGHT   ------" << "          ";
		SetColor(Blue, Black);
		cout << "------   DARKS   ------\n";
		SetColor(Green, Black);
		lights.print();
		cout << endl;
		SetColor(LightBlue, Black);
		darks.print(33, 1);
		SetColor(White, Black);
		SetCursor(0, line + 2);
	}

	Warrior* fight(List<Light*>* party, Warrior* enemy)
	{
		int partySize = party->getSize();
		Array<Light*> fighters;
		for (int i = 0; i < partySize; ++i)
		{
			Light* member = (*party)[i];
			member->resetSkill();
			fighters.add(member);
		}
		enemy->resetSkill();

		Array<int> turns;
		int count = 0;
		while (count <= partySize)
		{
			int warrior_ind = rand() % (partySize + 1);

			if (!turns.contains(warrior_ind))
			{
				turns.add(warrior_ind);
				count++;
			}
		}

		cout << "Turns for the battle rolled: ";
		for (int i = 0; i < partySize; i++)
		{
			if (turns[i] == partySize) { SetColor(LightBlue, Black); cout << enemy->getType(); SetColor(White, Black); }
			else { SetColor(Green, Black); cout << fighters[turns[i]]->getType(); SetColor(White, Black); }
			cout << " -> ";
		}
		if (turns[partySize] == partySize) { SetColor(LightBlue, Black); cout << enemy->getType() << "\n\n"; SetColor(White, Black); }
		else { SetColor(Green, Black); cout << fighters[turns[partySize]]->getType() << "\n\n"; SetColor(White, Black); }

		Array<Light*> fallen;
		auto deleteFallen = [&fallen]() // source: ChatGPT
			{
				for (int i = 0; i < fallen.getSize(); ++i)
					delete fallen[i];
			};

		while (party->getSize() > 0)
		{
			for (int turn = 0; turn <= partySize; turn++)
			{
				int warrior_ind = turns[turn];

				if (warrior_ind == partySize) // Enemy's one turn this round
				{
					int target_ind = rand() % party->getSize();
					Light* target = (*party)[target_ind];

					enemy->attack(target);

					if (target->getHP() == 0)
					{
						SetColor(Red, Black);
						cout << target->getType() << " was taken down!\n";
						SetColor(White, Black);

						party->remove(target_ind);
						fallen.add(target);

						if (party->getSize() == 0)
						{
							deleteFallen();
							return nullptr;
						}
					}

					SetColor(Green, Black);
					cout << "HP: " << target->getHP() << endl;
				}
				else // This Light character's scheduled turn
				{
					Light* member = fighters[warrior_ind];

					// They might have been defeated earlier in this round.
					if (member->getHP() > 0)
					{
						int hpBeforeAttack = enemy->getHP();
						member->attack(enemy, &fighters);

						if (enemy->getHP() == 0)
						{
							bool revive = false;
							if (enemy->getType() == "Zombie")
							{
								if (enemy->getSkill() && enemy->isSkillUsed() == false)
								{
									enemy->setHP(hpBeforeAttack);
									enemy->getSkill()->execute(enemy, member);
									if (enemy->getHP() == 1)
									{
										enemy->useSkill();
										revive = true;
									}
									else
									{
										cout << "Unlucky roll\n";
									}
								}
							}
							if (revive)
							{
								SetColor(Red, Black);
								cout << enemy->getType() << " is revived!\n";
								SetColor(White, Black);
							}
							else
							{
								SetColor(Red, Black);
								cout << enemy->getType() << " defeated!\n";
								SetColor(White, Black);

								deleteFallen();
								return enemy;
							}
						}

						SetColor(LightBlue, Black);
						cout << "HP: " << enemy->getHP() << endl;
					}
					else
					{
						cout << "Skipping turn of a fallen warrior\n";
					}
				}

				SetColor(DarkGray, Black);
				system("pause"); SetColor(White, Black);
			}
		}

		deleteFallen();
		return nullptr;
	}

	void game()
	{
		while (lights.getSize() > 0 && darks.getSize() > 0)
		{
			system("cls");
			print();

			int d_ind = rand() % darks.getSize();

			cout << "\n\n    Battle  Started    \n";
			cout << "-----------------------\n";
			cout << "Enemy selected: "; SetColor(LightBlue, Black);
			cout << darks[d_ind]->getType() << endl;
			cout << "HP: " << darks[d_ind]->getHP() << "\n\n"; SetColor(White, Black);

			Warrior* lost = fight(&lights, darks[d_ind]);

			SetCursor(33, line + 4);
			cout << "    Battle    Ended    "; SetCursor(33, line + 5);
			cout << "-----------------------"; SetCursor(33, line + 6);
			cout << darks[d_ind]; SetCursor(0, line + 8);

			if (lost == darks[d_ind])
			{
				darks.remove(d_ind);
				delete lost;
			}

			SetCursor(0, line + 7); SetColor(DarkGray, Black);
			system("pause"); SetColor(White, Black);
		}

		system("cls");
		if (lights.getSize() == 0)
		{
			SetColor(Red, Black); SetCursor(34, 5);
			cout << "YOU DIED"; SetColor(DarkGray, Black); SetCursor(0, 11);
		}
		else
		{
			SetCursor(30, 5);
			cout << "MISSION COMPLETE"; SetColor(Yellow, Black); SetCursor(34, 6);
			cout << "respect+"; SetColor(DarkGray, Black); SetCursor(0, 11);
		}
	}
};