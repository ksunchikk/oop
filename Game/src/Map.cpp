
#include "Map.h"
#include <fstream>
#include <string>

namespace game {
    SimpleTower* Map::addtower(SimpleTower::TypeOfLevel n_type, SimpleTower::TypeOfStrategy n_s_type, double n_x, double n_y) {
        SimpleTower* a = new SimpleTower(n_type, n_s_type, n_x, n_y);
        if (castle->getpurse() >= (*a).getCost()) {
            castle->buynewTower((*a).getCost());
            towers.push_back(a);
            return a;
        }
        return nullptr;
    }
    MagicTrap* Map::addtrap(Magic::TypeOfMagic n_type, double n_x, double n_y) {
        MagicTrap* a = new MagicTrap(n_type, n_x, n_y);
        if (castle->getpurse() >= (*a).getCost()) {
            castle->buynewTrap((*a).getCost());
            traps.push_back(a);
            return a;
        }
        return nullptr;
    }
    MagicTower* Map::addMagicTower(SimpleTower::TypeOfLevel n_type, SimpleTower::TypeOfStrategy n_s_type, Magic::TypeOfMagic n_m_type, double n_x, double n_y) {
        MagicTower* a = new MagicTower(n_m_type, n_type, n_s_type, n_x, n_y);
        if (castle->getpurse() >= (*a).getCost()) {
            castle->buynewTower((*a).getCost());
            towers.push_back(a);
            return a;
        }
        return nullptr;
    }
    Cell* Map::findCell(double n_x, double n_y) {
        for(std::vector<std::vector<Cell*>>::iterator i = cells.begin();i!=cells.end();i++) {
            for(std::vector<Cell*>::iterator m = (*i).begin();m!=(*i).end();m++) {
                double xx = (*m)->getX();
                double yy = (*m)->getY();
                if ((xx + 15) >= n_x && (xx - 15) <= n_x && (yy + 15) >= n_y && (yy - 15) <= n_y) {
                    return *m;
                }
            }
        }
        return nullptr;
    }
    void Map::moveAll(MainScene& m, double n_time) {
        std::vector<Enemy*>::iterator i = m.enemies.begin();
        std::vector<Enemy*>::iterator j = m.enemies.end();
        while (i != j) {
            double xx = (**i).getX();
            double yy = (**i).getY();
            double speed = (**i).getSpeed();
            if ((*(findCell(xx, yy - 29))).getIsRoad()) { (**i).setY(yy - speed * n_time); }
            if ((*(findCell(xx + 29, yy))).getIsRoad()) { (**i).setX(xx + speed * n_time); }
            i++;
        }
    }

    void Map::makeShot(MainScene& m, double n_time) {
        std::vector<SimpleTower*>::iterator u = towers.begin();
        std::vector<SimpleTower*>::iterator d = towers.end();
        while (u != d) {
            if ((**u).getStrategy() == SimpleTower::TypeOfStrategy::HealthDown) { 
                if((**u).findHealthDownEnemy(m) != m.enemies.end())
                (**u).addDamage(**((**u).findHealthDownEnemy(m)), n_time); 
            }
                if ((**u).getStrategy() == SimpleTower::TypeOfStrategy::HealthUp) {
                    if ((**u).findHealthUpEnemy(m) != m.enemies.end())
                    (**u).addDamage(**((**u).findHealthUpEnemy(m)), n_time);
                }
                if ((**u).getStrategy() == SimpleTower::TypeOfStrategy::Speed) {
                    if ((**u).findSpeedUpEnemy(m) != m.enemies.end())
                    (**u).addDamage(**(**u).findSpeedUpEnemy(m), n_time);
                }
                if ((**u).getStrategy() == SimpleTower::TypeOfStrategy::Location) {
                    if ((**u).findCloseEnemy(m) != m.enemies.end())
                    (**u).addDamage(**((**u).findCloseEnemy(m)), n_time);

                }
                if ((**u).getStrategy() == SimpleTower::TypeOfStrategy::LocationFromCastle) {
                    if ((**u).findCloseEnemyToCastle(m) != m.enemies.end())
                    (**u).addDamage(**((**u).findCloseEnemyToCastle(m)), n_time);
                }
            u++;
        }

    }
    void Map::makeTrapShot(MainScene& m, double n_time) {
        std::vector<MagicTrap*>::iterator u = traps.begin();
        std::vector<MagicTrap*>::iterator d = traps.end();
        while (u != d) {
            if ((n_time-(*u)->lastshot) >= 4) {
                std::vector<Enemy*>::iterator i = m.enemies.begin();
                std::vector<Enemy*>::iterator j = m.enemies.end();
                double xt = (**u).getX();
                double yt = (**u).getY();
                while (i != j) {
                    double xx = (**i).getX();
                    double yy = (**i).getY();
                    if (xt + 15 >= xx && xt - 15 <= xx && yt + 15 >= yy && yt - 15 <= yy) {
                        std::vector<Enemy*>::iterator k = m.enemies.begin();
                        std::vector<Enemy*>::iterator l = m.enemies.end();
                        (**u).addSpell(**i);
                        (*u)->lastshot = n_time;
                        while (k != l) {
                            double xx = (**k).getX();
                            double yy = (**k).getY();
                            double distance = sqrt((xt - xx) * (xt - xx) + (yt - yy) * (yt - yy));
                            if (distance <= (**u).getArea()) (**u).addSpell(**k);
                            k++;
                        }
                        return;
                    }
                    i++;
                }
            }
            u++;

        }

    }
    void Map::upgradeTower(SimpleTower::TypeOfLevel n_type, SimpleTower& n_tow) {
        if (n_tow.getLevel() == SimpleTower::TypeOfLevel::Strong) return;
        if (n_tow.getLevel() == SimpleTower::TypeOfLevel::Middle && n_type == SimpleTower::TypeOfLevel::Strong) {
            if (n_tow.Otype == ObjectOnMap::Type::MAGICTOWER) {
                MagicTower a(n_tow.getMagic()->getType(), n_type, n_tow.getStrategy(), n_tow.getX(), n_tow.getY());
                n_tow.setArea(a.getArea());
                n_tow.setDamage(a.getDamage());
                n_tow.setLevel(a.getLevel());
                n_tow.setSpeed(a.getSpeed());
                castle->buynewTower(a.getCost() - n_tow.getCost());
                n_tow.setCost(a.getCost());
            }
            else {
                SimpleTower a(n_type, n_tow.getStrategy(), n_tow.getX(), n_tow.getY());
                n_tow.setArea(a.getArea());
                n_tow.setDamage(a.getDamage());
                n_tow.setLevel(a.getLevel());
                n_tow.setSpeed(a.getSpeed());
                castle->buynewTower(a.getCost() - n_tow.getCost());
                n_tow.setCost(a.getCost());
            }

        }
        else return;
        if (n_tow.getLevel() == SimpleTower::TypeOfLevel::Simple && (n_type == SimpleTower::TypeOfLevel::Strong || n_type == SimpleTower::TypeOfLevel::Middle)) {
            if (n_tow.Otype == ObjectOnMap::Type::MAGICTOWER) {
                MagicTower a(n_tow.getMagic()->getType(), n_type, n_tow.getStrategy(), n_tow.getX(), n_tow.getY());
                n_tow.setArea(a.getArea());
                n_tow.setDamage(a.getDamage());
                n_tow.setLevel(a.getLevel());
                n_tow.setSpeed(a.getSpeed());
                castle->buynewTower(a.getCost() - n_tow.getCost());
                n_tow.setCost(a.getCost());
            }
            else {
                SimpleTower a(n_type, n_tow.getStrategy(), n_tow.getX(), n_tow.getY());
                n_tow.setArea(a.getArea());
                n_tow.setDamage(a.getDamage());
                n_tow.setLevel(a.getLevel());
                n_tow.setSpeed(a.getSpeed());
                castle->buynewTower(a.getCost() - n_tow.getCost());
                n_tow.setCost(a.getCost());
            }
        }
        else return;
    }
    void Map::init(const std::string& f_name) {
        std::ifstream fin(f_name);
        if (!fin.is_open()) throw std::runtime_error("Can't open this file");
        int amount;
        int type;
        int yy = 15;
        int k = 0, p = 1;
        while (k < 30) {
            int xx = 15;
            std::vector<Cell*> c_;
            while (p < 40) {
                fin >> amount;
                fin >> type;
                Cell::TypeOfCell Type;
                if (type == 0) {
                    Type = Cell::TypeOfCell::FOREST;
                }
                if (type == 1) {
                    Type = Cell::TypeOfCell::LEA;
                }
                if (type == 2) {
                    Type = Cell::TypeOfCell::ROAD;
                }
                for (int i = 0; i < amount; i++) {
                    c_.push_back(new Cell(Type, xx, yy));
                    xx += 30;
                    p++;
                }
            }
            yy += 30;
            k++;
            p = 0;
            cells.push_back(c_);
        }
    }
    void Map::save(MainScene& m, const string& f_name) {
        std::ofstream fout(f_name);
        int type;
        if (castle != nullptr) {
            int pur = castle->getpurse();
            int mhp = castle->getmaxhealth();
            int hp = castle->getcurhealth();
            bool al = castle->getalive();
            double xx = castle->getX();
            double yy = castle->getY();
            type = 0;
            fout << type <<" " << pur << " "<< mhp << " "<< hp <<" " << al <<" " << xx << " " << yy<< " ";
        }
        for (int i = 0; i < 2; i++) {
            int amount = den[i]->getAmount();
            double xx = den[i]->getX();
            double yy = den[i]->getY();
            type = 1;
            fout << type << " "<< amount<< " " << xx << " "<< yy<< " ";
            std::vector<Enemy>::iterator enemies = den[i]->getEnemies().begin();
            for (int j = 0; j < amount; j++) {
                int enem;
                int time = enemies->getTime();
                if (enemies->getTypeOfLevel() == Enemy::TypeOfLevel::Simple) {
                    enem = 0;
                }
                if (enemies->getTypeOfLevel() == Enemy::TypeOfLevel::Middle) {
                    enem = 1;
                }
                if (enemies->getTypeOfLevel() == Enemy::TypeOfLevel::Strong) {
                    enem = 2;
                }
                fout << enem <<" "<< time<< " ";
                enemies++;
            }
        }
        std::vector<SimpleTower*>::iterator u = towers.begin();
        std::vector<SimpleTower*>::iterator d = towers.end();
        if (u != d) {
            while (u != d) {
                int lev;
                int str;
                double xx = (*u)->getX();
                double yy = (*u)->getY();
                double last = (*u)->lastShot;
                SimpleTower::TypeOfLevel tow = (*u)->getLevel();
                SimpleTower::TypeOfStrategy tow1 = (*u)->getStrategy();
                if (tow == SimpleTower::TypeOfLevel::Simple) {
                    lev = 0;
                }
                if (tow == SimpleTower::TypeOfLevel::Middle) {
                    lev = 1;
                }
                if (tow == SimpleTower::TypeOfLevel::Strong) {
                    lev = 2;
                }
                if (tow1 == SimpleTower::TypeOfStrategy::Location) {
                    str = 0;
                }
                if (tow1 == SimpleTower::TypeOfStrategy::LocationFromCastle) {

                    str = 1;
                }
                if (tow1 == SimpleTower::TypeOfStrategy::HealthUp) {
                    str = 2;
                }
                if (tow1 == SimpleTower::TypeOfStrategy::HealthDown) {
                    str = 3;
                }
                if (tow1 == SimpleTower::TypeOfStrategy::Speed) {
                    str = 4;
                }
                int mag;
                if ((*u)->getMagic() != nullptr) {
                    Magic::TypeOfMagic m_type = (*u)->getMagic()->getType();
                    type = 3;
                    if (m_type == Magic::TypeOfMagic::POISONING) {
                        mag = 0;
                    }
                    if (m_type == Magic::TypeOfMagic::WEAKNESS) {
                        mag = 1;
                    }
                    if (m_type == Magic::TypeOfMagic::SLOWDOWN) {
                        mag = 2;
                    }
                    fout << type <<" " << lev << " " << str << " " << xx << " "<< yy<< " " << last << " " << mag << " ";
                }
                else {
                    type = 2;
                    fout << type <<" "  << lev << " " << str << " " << xx << " "<< yy << " " << last << " ";
                }
                u++;
            }
        }
        std::vector<MagicTrap*>::iterator uu = traps.begin();
        std::vector<MagicTrap*>::iterator dd = traps.end();
        if (uu != dd) {
            while (uu != dd) {
                double xx = (**uu).getX();
                double yy = (**uu).getY();
                int mag;
                Magic::TypeOfMagic m_type = (**uu).getMagic()->getType();
                type = 4;
                if (m_type == Magic::TypeOfMagic::POISONING) {
                    mag = 0;
                }
                if (m_type == Magic::TypeOfMagic::WEAKNESS) {
                    mag = 1;
                }
                if (m_type == Magic::TypeOfMagic::SLOWDOWN) {
                    mag = 2;
                }
                fout << type << " "  << xx << " " << yy << " " << mag << " ";
                uu++;
            }
            std::vector<Enemy*>::iterator uuu = m.enemies.begin();
            std::vector<Enemy*>::iterator ddd = m.enemies.end();
            while (uuu != ddd) {
                int lev;
                double speed = (**uuu).getSpeed();
                double weakness = (**uuu).getWeakness();
                double hp = (**uuu).getHp();
                double xx = (*uuu)->getX();
                double yy = (*uuu)->getY();
                type = 5;
                Enemy::TypeOfLevel tow = (*uuu)->getTypeOfLevel();
                if (tow == Enemy::TypeOfLevel::Simple) {
                    lev = 0;
                }
                if (tow == Enemy::TypeOfLevel::Middle) {
                    lev = 1;
                }
                if (tow == Enemy::TypeOfLevel::Strong) {
                    lev = 2;
                }
                fout << type << " " << lev << " " << speed << " " << weakness << " " << hp << " " << xx << " " << yy << " ";
                std::vector<Magic*> magic = (*uuu)->getVecMagic();
                std::vector<Magic*>::iterator i = magic.begin();
                std::vector<Magic*>::iterator j = magic.end();
                while (i != j) {
                    int maxtime = (*i)->getMaxTime();
                    double timeleft = (*i)->getTime();
                    bool accept = (*i)->getAccept();
                    double pow = (*i)->getPower();
                    int mag;
                    Magic::TypeOfMagic m_type = (*i)->getType();
                    if (m_type == Magic::TypeOfMagic::POISONING) {
                        mag = 0;
                    }
                    if (m_type == Magic::TypeOfMagic::WEAKNESS) {
                        mag = 1;
                    }
                    if (m_type == Magic::TypeOfMagic::SLOWDOWN) {
                        mag = 2;
                    }
                    fout << mag  <<" " << maxtime << " " << accept << "  "<< pow<< " " << timeleft << " ";
                    i++;
                }
                uuu++;
            }
            fout << -1 << " ";
        }
        fout << -1;
    }

    void Map::load(MainScene& m, const string& f_name) {
        std::ifstream fin(f_name);
        if (!fin.is_open()) throw std::runtime_error("Can't open this file");
        int type = 0;
        int i = 0;
        while (type != -1) {
            fin >> type;
            if (type == 0) {
                int pur;
                int mhp;
                int hp;
                bool al;
                double xx;
                double yy;
                fin >> pur >> mhp >> hp >> al >> xx >> yy;
                castle = new Castle(pur, mhp, hp, al, xx, yy);
                continue;
            }
            if (type == 1) {
                int amount;
                double xx;
                double yy;
                fin >> amount >> xx >> yy;
                Den* D = new Den(amount, {}, xx, yy);
                std::vector<Enemy> enemies;
                for (int i = 0; i < amount; i++) {
                    int enem;
                    int time;
                    fin >> enem >> time;
                    if (enem == 0) {
                        Enemy a = *(new Enemy(Enemy::TypeOfLevel::Simple, time, xx, yy));
                        enemies.push_back(a);
                    }
                    if (enem == 1) {
                        Enemy a = *(new Enemy(Enemy::TypeOfLevel::Middle, time, xx, yy));
                        enemies.push_back(a);
                    }
                    if (enem == 2) {
                        Enemy a = *(new Enemy(Enemy::TypeOfLevel::Strong, time, xx, yy));
                        enemies.push_back(a);
                    }
                }
                (*D).setEnemies(enemies);
                den[i] = D;
                i++;
                continue;
            }
            if (type == 2) {
                int lev;
                int str;
                double xx;
                double yy;
                double last;
                fin >> lev >> str >> xx >> yy >> last;
                SimpleTower::TypeOfLevel tow;
                SimpleTower::TypeOfStrategy tow1;
                if (lev == 0) {
                    tow = SimpleTower::TypeOfLevel::Simple;
                }
                if (lev == 1) {
                    tow = SimpleTower::TypeOfLevel::Middle;
                }
                if (lev == 2) {
                    tow = SimpleTower::TypeOfLevel::Strong;
                }
                if (str == 0) {
                    tow1 = SimpleTower::TypeOfStrategy::Location;
                }
                if (str == 1) {
                    tow1 = SimpleTower::TypeOfStrategy::LocationFromCastle;
                }
                if (str == 2) {
                    tow1 = SimpleTower::TypeOfStrategy::HealthUp;
                }
                if (str == 3) {
                    tow1 = SimpleTower::TypeOfStrategy::HealthDown;
                }
                if (str == 4) {
                    tow1 = SimpleTower::TypeOfStrategy::Speed;
                }
                towers.push_back(new SimpleTower(tow, tow1, xx, yy));
                (**(towers.end())).lastShot = last;
                continue;
            }
            if (type == 3) {
                int lev;
                int str;
                double xx;
                double yy;
                double last;
                int mag;
                fin >> lev >> str >> xx >> yy >> last >> mag;
                SimpleTower::TypeOfLevel tow;
                SimpleTower::TypeOfStrategy tow1;
                Magic::TypeOfMagic m_type;
                if (lev == 0) {
                    tow = SimpleTower::TypeOfLevel::Simple;
                }
                if (lev == 1) {
                    tow = SimpleTower::TypeOfLevel::Middle;
                }
                if (lev == 2) {
                    tow = SimpleTower::TypeOfLevel::Strong;
                }
                if (str == 0) {
                    tow1 = SimpleTower::TypeOfStrategy::Location;
                }
                if (str == 1) {
                    tow1 = SimpleTower::TypeOfStrategy::LocationFromCastle;
                }
                if (str == 2) {
                    tow1 = SimpleTower::TypeOfStrategy::HealthUp;
                }
                if (str == 3) {
                    tow1 = SimpleTower::TypeOfStrategy::HealthDown;
                }
                if (str == 4) {
                    tow1 = SimpleTower::TypeOfStrategy::Speed;
                }
                if (mag == 0) {
                    m_type = Magic::TypeOfMagic::POISONING;
                }
                if (mag == 1) {
                    m_type = Magic::TypeOfMagic::WEAKNESS;
                }
                if (mag == 2) {
                    m_type = Magic::TypeOfMagic::SLOWDOWN;
                }
                towers.push_back(new MagicTower(m_type, tow, tow1, xx, yy));
                (**(towers.end())).lastShot = last;
                continue;
            }
            if (type == 4) {
                double xx;
                double yy;
                int mag;
                fin >> xx >> yy >> mag;
                Magic::TypeOfMagic m_type;
                if (mag == 0) {
                    m_type = Magic::TypeOfMagic::POISONING;
                }
                if (mag == 1) {
                    m_type = Magic::TypeOfMagic::WEAKNESS;
                }
                if (mag == 2) {
                    m_type = Magic::TypeOfMagic::SLOWDOWN;
                }
                traps.push_back(new MagicTrap(m_type, xx, yy));
                continue;
            }
            if (type == 5) {
                int n_type;
                double speed;
                double weakness;
                double hp;
                double xx;
                double yy;
                fin >> n_type >> speed >> weakness >> hp >> xx >> yy;
                Enemy::TypeOfLevel tow;
                if (n_type == 0) {
                    tow = Enemy::TypeOfLevel::Simple;
                }
                if (n_type == 1) {
                    tow = Enemy::TypeOfLevel::Middle;
                }
                if (n_type == 2) {
                    tow = Enemy::TypeOfLevel::Strong;
                }
                m.enemies.push_back(new Enemy(tow));
                (**(m.enemies.end())).setHp(hp);
                (**(m.enemies.end())).setSpeed(speed);
                (**(m.enemies.end())).setX(xx);
                (**(m.enemies.end())).setY(yy);
                (**(m.enemies.end())).setWeak(weakness);
                std::vector<Magic*> magic;
                fin >> n_type;
                while (n_type != -1) {
                    int maxtime;
                    double timeleft;
                    bool accept;
                    double pow;
                    fin >> n_type;
                    if (n_type != -1) {
                        fin >> maxtime >> accept >> pow >> timeleft;
                        Magic::TypeOfMagic m_type;
                        if (n_type == 0) {
                            m_type = Magic::TypeOfMagic::POISONING;
                        }
                        if (n_type == 1) {
                            m_type = Magic::TypeOfMagic::WEAKNESS;
                        }
                        if (n_type == 2) {
                            m_type = Magic::TypeOfMagic::SLOWDOWN;
                        }
                        (**(m.enemies.end())).addMagic(*(new Magic(maxtime, m_type, pow, accept, timeleft)));
                    }

                }
                continue;
            }
        }

    }
}