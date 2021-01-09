
#ifndef _MAGIC_H
#define _MAGIC_H


namespace game {
    class Magic {
    protected:
        int maxtime;
        double timeleft;
        bool accept;
        double power;
    public: 

        enum class TypeOfMagic {POISONING, WEAKNESS, SLOWDOWN};
        TypeOfMagic type;
        Magic(int n_maxtime = 10, TypeOfMagic n_type = TypeOfMagic::POISONING, double n_pow=10, bool n_accep=false, double n_time=0);
        ~Magic(){}
        virtual int getMaxTime()const { return maxtime; }
        virtual TypeOfMagic getType() const { return type; }
        virtual double getTime()const { return timeleft; }
        virtual bool getAccept()const { return accept; }
        virtual double getPower() const { return power; }
        virtual void setPower(double n_pow) { power = n_pow; }
        virtual void setTime(double n_time) { timeleft = n_time; }
        virtual void setMTime(int n_time) { maxtime = n_time; }
        virtual void setType(TypeOfMagic n_type) { type = n_type; }
        virtual void setAccept(bool n_accep) { accept = n_accep; }
        

    };

}
#endif