/// add -1 before Infection:
/// sometimes no brackets !!

#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin ("d24.in");
ofstream fout("d24.out");

const int LG=101,ALLCHR=301,NARMY=3,NGROUP=101,NDMGTYPE=6;
int vdmgtypeindex[ALLCHR+3],vround[NARMY+3][NGROUP+3],defpower,defchosenpower;
int ngroup,initiative,igroup,iarmy,jgroup,dmgreceived,reaction,dmgmax,attpower,attdmgtype;
int defchosenhp,dmgdealt,nunit,dmg,dmgtype;
int iround,nwinner,nkilled;
int ialivegroup;
char vchr[LG+3],chr;
bool fighton,isdead[NARMY+3][NGROUP+3],isdmgtype[ALLCHR];


struct sctalivegroup
{
    int iarmy,igroup;
} alivegroup,defchosen,att,def;


struct sctgroup
{
    int nunit,hp,dmg,dmgtype,initiative,dmgreceived;
    int vreaction[NDMGTYPE];
    sctalivegroup defchosen;
} group,NULLGROUP;

vector <sctalivegroup> valivegroup;
vector <sctgroup> varmy[NGROUP];

/// bludgeoning 1
/// cold 2
/// fire 3
/// radiation 4
/// slashing 5

void setisdmgchar()
{
    isdmgtype['b']=isdmgtype['c']=isdmgtype['f']=isdmgtype['r']=isdmgtype['s']=1;
}

bool bypower(sctalivegroup a,sctalivegroup b)
{
    int powera=varmy[a.iarmy][a.igroup].nunit*varmy[a.iarmy][a.igroup].dmg;
    int powerb=varmy[b.iarmy][b.igroup].nunit*varmy[b.iarmy][b.igroup].dmg;

    if (powera==powerb)
    {
        return varmy[a.iarmy][a.igroup].initiative>varmy[a.iarmy][a.igroup].initiative;
    }
    return powera>powerb;
}

bool byinitiative(sctalivegroup a,sctalivegroup b)
{
    return varmy[a.iarmy][a.igroup].initiative>varmy[b.iarmy][b.igroup].initiative;
}

void setdmgtypeindex()
{
    vdmgtypeindex['b']=1;
    vdmgtypeindex['c']=2;
    vdmgtypeindex['f']=3;
    vdmgtypeindex['r']=4;
    vdmgtypeindex['s']=5;
}

void attacking()
{
    sort(valivegroup.begin()+1,valivegroup.end(),byinitiative);
    for (ialivegroup=1; ialivegroup<valivegroup.size(); ++ialivegroup)
    {
        att=valivegroup[ialivegroup];
        nunit=varmy[att.iarmy][att.igroup].nunit;
        if (!nunit)
        {
            continue;
        }
        defchosen=varmy[att.iarmy][att.igroup].defchosen;

        if (!defchosen.iarmy || !defchosen.igroup)
        {
            continue;
        }

        dmg=varmy[att.iarmy][att.igroup].dmg ;
        dmgtype=varmy[att.iarmy][att.igroup].dmgtype;
        reaction=varmy[defchosen.iarmy][defchosen.igroup].vreaction[dmgtype];
        dmgdealt=nunit * dmg * (reaction+1);
        defchosenhp=varmy[defchosen.iarmy][defchosen.igroup].hp;

        nkilled=( dmgdealt /  defchosenhp);

        if(!nkilled)
        {
            continue;
        }

        defchosen=varmy[att.iarmy][att.igroup].defchosen;
        varmy[defchosen.iarmy][defchosen.igroup].nunit-=nkilled;
    }

    for (ialivegroup=1; ialivegroup<valivegroup.size(); ++ialivegroup)
    {
        alivegroup=valivegroup[ialivegroup];
        if (varmy[alivegroup.iarmy][alivegroup.igroup].nunit<=0)
        {
            isdead[alivegroup.iarmy][alivegroup.igroup]=1;
            valivegroup.erase(valivegroup.begin()+ialivegroup);
            --ialivegroup;
        }
    }
}

void targetselection()
{
    sort(valivegroup.begin()+1,valivegroup.end(),bypower);

    fighton=0;
    for (ialivegroup=1; ialivegroup<valivegroup.size(); ++ialivegroup)
    {
        att=valivegroup[ialivegroup];
        attpower=varmy[att.iarmy][att.igroup].nunit*varmy[att.iarmy][att.igroup].dmg;
        attdmgtype=varmy[att.iarmy][att.igroup].dmgtype;
        def.iarmy=1+(!(att.iarmy-1));

        defchosen.iarmy=0;
        defchosen.igroup=0;

        for (def.igroup=1; def.igroup<varmy[def.iarmy].size(); ++def.igroup)
        {
            if (isdead[def.iarmy][def.igroup] || vround[def.iarmy][def.igroup]==iround)
            {
                continue;
            }
            fighton=1;

            reaction=varmy[def.iarmy][def.igroup].vreaction[attdmgtype];
            varmy[def.iarmy][def.igroup].dmgreceived = dmgreceived = attpower * ( 1 + reaction);

            dmgmax=varmy[defchosen.iarmy][defchosen.igroup].dmgreceived;
            if (dmgreceived > dmgmax)
            {
                defchosen=def;
            }
            else if (dmgreceived == dmgmax )
            {
                defpower=varmy[def.iarmy][def.igroup].nunit*varmy[def.iarmy][def.igroup].dmg;
                defchosenpower=varmy[defchosen.iarmy][defchosen.igroup].nunit*varmy[defchosen.iarmy][defchosen.igroup].dmg;
                if (defpower > defchosenpower)
                {
                    defchosen=def;
                }
                else if (defpower == defchosenpower)
                {
                    if (varmy[def.iarmy][def.igroup].initiative > varmy[defchosen.iarmy][defchosen.igroup].initiative)
                    {
                        defchosen=def;
                    }
                }
            }
        }
        if (!fighton) break;


        dmgreceived=varmy[defchosen.iarmy][defchosen.igroup].dmgreceived;
        if(!dmgreceived)
        {
            defchosen.iarmy=0;
            defchosen.igroup=0;
            varmy[att.iarmy][att.igroup].defchosen=defchosen;
        }
        else
        {
            vround[defchosen.iarmy][defchosen.igroup]=iround;
            varmy[att.iarmy][att.igroup].defchosen=defchosen;

        }
    }
    if (!fighton) return;;

}

void parse()
{
    fin.getline(vchr+1,LG);
    varmy[0].push_back(NULLGROUP);
    varmy[iarmy=igroup=1].push_back(NULLGROUP);
    varmy[2].push_back(NULLGROUP);
    valivegroup.push_back({0,0});


    while (fin>>group.nunit)
    {
        if (group.nunit<0)
        {
            fin >> vchr+1 >> group.nunit;
            ++iarmy;
            igroup=1;
            if (iarmy==3)
            {
                break;
            }
        }

        fin >> vchr+1 >> vchr+1 >> vchr+1 >> group.hp >> vchr+1 >> vchr+1 ;
        fin >> vchr+1;

        if (vchr[1]=='(')
        {
            if (vchr[strlen(vchr+1)]=='e' && vchr[strlen(vchr+1)-1]=='n') // immune
            {
                fin >> vchr+1 >> vchr+1 ; /// to...
                while (isdmgtype[vchr[1]])
                {
                    group.vreaction[vdmgtypeindex[vchr[1]]]=-1;
                    fin >> vchr+1 ;
                }
            }
            if ( vchr[strlen(vchr+1)]=='k') /// weak
            {
                fin >> vchr+1 >> vchr+1 ; /// to...
                while (isdmgtype[vchr[1]])
                {
                    group.vreaction[vdmgtypeindex[vchr[1]]]=1;
                    fin>>vchr+1;
                }
            }
            if (vchr[strlen(vchr+1)]=='e' && vchr[strlen(vchr+1)-1]=='n') // immune
            {
                fin >> vchr+1 >> vchr+1 ; /// to...
                while (isdmgtype[vchr[1]])
                {
                    group.vreaction[vdmgtypeindex[vchr[1]]]=-1;
                    fin >> vchr+1 ;
                }
            }
        }

        fin >> vchr+1 >> vchr+1 >> vchr+1 >> vchr+1;
        fin >> group.dmg >> vchr+1;
        group.dmgtype=vdmgtypeindex[vchr[1]];
        fin >> vchr+1>> vchr+1 >> vchr+1 >> group.initiative ;
        valivegroup.push_back({iarmy,igroup});
        varmy[iarmy].push_back(group);
        group=NULLGROUP;
        ++igroup;
    }
}

int main()
{
    setdmgtypeindex();
    setisdmgchar();
    parse();

    fighton=1;
    while (fighton)
    {
        ++iround;
        targetselection();
        if (!fighton) break;
        attacking();
    }

    for (ialivegroup=1; ialivegroup<valivegroup.size(); ++ialivegroup)
    {
        alivegroup=valivegroup[ialivegroup];
        group=varmy[alivegroup.iarmy][alivegroup.igroup];
        nwinner += group.nunit;
    }

    fout << " part one " << nwinner << "\n";

    return 0;
}
