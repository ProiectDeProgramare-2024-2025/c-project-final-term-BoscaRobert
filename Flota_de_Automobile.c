#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

struct masina
{
   char marca[256],nume[256],culoare[256];
   int locuri, disponibil;
};

int initializeaza_lista(struct masina v[256],char *nume)
{
    int i;
    char c,aux[256],*p;
    FILE *fisier = fopen(nume, "r");
    if(fisier==NULL)
       printf("Fisierul Nu Exista.\n");
    else{
        fgets(aux,256,fisier);
        i=0;
         while(fgets(aux,256,fisier))
            {
                p=strtok(aux," ");
                strcpy(v[i].marca,p);
                p=strtok(NULL," ");
                strcpy(v[i].nume,p);
                p=strtok(NULL," ");
                strcpy(v[i].culoare,p);
                p=strtok(NULL," ");
                v[i].locuri=(int)(*p-48);
                p=strtok(NULL," ");
                v[i].disponibil=(int)(*p-48);
                i++;
            }       
        }
    return i+1;
}

int initializeaza_lista_fara_header(struct masina v[256],char *nume)
{
    int i;
    char c,aux[256],*p;
    FILE *fisier = fopen(nume, "r");
    if(fisier==NULL)
       printf("Fisierul Nu Exista.\n");
    else{
        i=0;
         while(fgets(aux,256,fisier))
            {
                p=strtok(aux," ");
                strcpy(v[i].marca,p);
                p=strtok(NULL," ");
                strcpy(v[i].nume,p);
                p=strtok(NULL," ");
                strcpy(v[i].culoare,p);
                p=strtok(NULL," ");
                v[i].locuri=(int)(*p-48);
                p=strtok(NULL," ");
                v[i].disponibil=(int)(*p-48);
                i++;
            }       
        }
    return i+1;
}

void afisare_din_fisier(char *nume)
{
    printf("Marca Nume Culoare");
    char c;
    FILE *fisier = fopen(nume, "r");
    if(fisier==NULL)
       printf("Fisierul Nu Exista.\n");
    else{
         printf("Continutul Fisierului:\n");
         while(c!=EOF){
            printf("%c",c);
            c=fgetc(fisier);
            }
        }
}
void afisare_din_lista(struct masina v[256],int n)
{
    printf("|Index||    Marca    ||    Nume     ||  Culoare    || Locuri || Liber |\n");
    printf("=======================================================================\n");
    for(int i=0;i<n-1;i++)
    {
        printf("\x1b[1m|%4d \x1b[1m||\x1b[36m %-12s\x1b[0m\x1b[1m||\x1b[35m %-12s\x1b[0m\x1b[1m||\x1b[38;5;229m %-12s\x1b[0m\x1b[1m||\x1b[1m %4d   \x1b[0m\x1b[1m||\x1b[1m%4d   \x1b[0m\x1b[1m|\n",i+1,v[i].marca,v[i].nume,v[i].culoare,v[i].locuri,v[i].disponibil);
    }
    printf("=======================================================================\n");

}
void actualizare(struct masina v[256],int n)
{
    int index,optiune;
    char schimb[256];
    printf("Adaugati Indexul masini pe care o vreti actualizata :");
    scanf("%d",&index);
    if(index>n||index<0)
    {
        printf("\x1b[31mNu exista masina la indexul %d, lista nu s-a actualizat \x1b[0m\x1b[1m\n",index);
        sleep(3);
        goto preamare;
    }
    printf("Ce se doreste modificat? \n\n1)Marca\n2)Numele\n3)culoare\n4)Nr de Locuri\n5)Disponibilitatea\n\n");
    scanf("%d",&optiune);
    printf("Introduceti Modificarea(cu ce se inlocieste) \n\n");
    scanf("%s",schimb);
    switch (optiune)
    {
        case 1:
           strcpy(v[index-1].marca,schimb);
           break;
        case 2:
           strcpy(v[index-1].nume,schimb);
           break;
        case 3:
           strcpy(v[index-1].culoare,schimb);
           break;
        case 4:
           v[index-1].locuri=(int)(schimb[0]-48);
        case 5:
           v[index-1].disponibil=(int)(schimb[0]-48);
    }
    preamare:
}
void adaugare(struct masina v[256],int n)
{
    int index,a;
    char aux[256];
    printf("Adaugati Indexul la care se va adauga masina ");
    scanf("%d",&index);
    if(index>n||index<0)
    {
        printf("\x1b[31mNu exista masina la indexul %d, lista nu s-a actualizat \x1b[0m\x1b[1m\n",index);
        sleep(3);
        goto preamare;
    }
    index-=1;
    for(int i=n;i>index;i--)
    {
        v[i]=v[i-1];
    }
    printf("Introduceti detalile masinii \n\nMarca: ");
    scanf("%s",aux);
    strcpy(v[index].marca,aux);
    printf("\nNume: ");
    scanf("%s",aux);
    strcpy(v[index].nume,aux);
    printf("\nCuloare: ");
    scanf("%s",aux);
    strcpy(v[index].culoare,aux);
    printf("\nNr de Locuri: ");
    scanf("%d",&a);
    v[index].locuri=a;
    printf("\nDisponibilitate: ");
    scanf("%d",&a);
    v[index].disponibil=a;
    printf("\n\x1b[32mMasina Adaugata\x1b[0m\x1b[1m\n");
    preamare:
    ;
}
void stergere(struct masina v[256],int n)
{
    int index;
    printf("Introduceti Indexul masinii pe care o doriti stearsa:\n\n");
    scanf("%d",&index);
    if(index>n||index<0)
    {
        printf("\x1b[31mNu exista masina la indexul %d, lista nu s-a actualizat \x1b[0m\x1b[1m\n",index);
        sleep(3);
        goto preamare;
    }
    for(int i=index-1;i<n-1;i++) 
       v[i]=v[i+1];
    preamare:

}
int cautare(struct masina v[256],int n)
{
    int gasit=0,i;
    char c[256],x[256];

    printf("Introduceti Detalile complete a masinii pe care doriti sa o cautati, adica\nseparat prin spatii: Marca, Firma, Culoarea, nr de locuri, si disponibilitatea (0/1)\n\n");
    getchar();
    fgets(x,256,stdin);
    FILE *fisier = fopen("masini.txt", "r");
    if(fisier==NULL)
       printf("Fisierul Nu Exista.\n");
    else{
        i=0;
         while(fgets(c,256,fisier))
            {
                if(strcmp(c,x)==0)
                {
                    goto GASIT;
                }
                i++;
            }       
        }
    GASIT: return i;
}
void rezerva(struct masina v[256],int n,int *x)
{
    int i;
    system("clear");
    afisare_din_lista(v,n);
    printf("Introduceti indexul masini pe care vreti sa o rezervati\n");
    scanf("%d",&i);
    i--;
    if(v[i].disponibil==0)
        printf("\x1b[31mMasina Nu Este Disponibila\x1b[0m\x1b[1m\n");
    else 
    {
        FILE *fisier = fopen("rezervare.txt", "w");
        fprintf(fisier,"%s %s %s %d %d\n",v[i].marca,v[i].nume,v[i].culoare,v[i].locuri,v[i].disponibil);
        fclose(fisier);
        printf("\x1b[32mRezervare Realizata cu Succres\x1b[0m\x1b[1m\n");
        *x=i;
    }

}
void anuleaza()
{
    fopen("rezervare.txt","w");
}

void salveaza(struct masina v[256],int n)
{
    FILE  *fisier = fopen("masini.txt","w");
    fprintf(fisier,"Marca,  Nume,  Culoare,  Locuri,  Disponibilitate(1=disponibil,0=indisponibil)\n");
    for(int i=0;i<n-1;i++) 
    {
        fprintf(fisier,"%s %s %s %d %d\n",v[i].marca,v[i].nume,v[i].culoare,v[i].locuri,v[i].disponibil);
    }
    fclose(fisier);
}

int main()
{
    struct masina v[256],r[256];
    int n,n2,optiune1,optiune2,optiune3,ocupata;
    n=initializeaza_lista(v,"masini.txt");
    Inceput_Meniu: 
    system("clear");   
    printf("\x1b[1m-----------------------------\n\x1b[38;5;123mFlota auto pentru închiriere\x1b[0m\x1b[1m\n-----------------------------\n\n");

    printf("\x1b[1m1)Modificarea Flotei De Masini\n2)Cautarea Unui Autoturism In Flota Auto\n3)Vizualizarea Tuturor Vehiculelor Din Flota\n4)Rezerva o Masina sau Anuleaza Rezervarea\n5)Salveaza Modificarile\n6)Iesire\n\n");
    scanf("%d",&optiune1);
    if(optiune1>6) 
    {
    system("clear");
    printf("\n\x1b[0\x1b[31moptiune invalida\x1b[0m\x1b[1m\n");
    sleep(1);
    goto Inceput_Meniu;}
    switch(optiune1)
    {
        case 1:
           ACT:
           system("clear");
           afisare_din_lista(v,n);
           printf("\x1b[34mModificaera Flotei de Masini\x1b[0m\x1b[1m\n-----------------------------------\n");
           printf("1)Actualizarea Unei Masini din flota\n2)Adaugarea Unei Masini in Flota\n3)Stergerea Unei Masini Din Flota\n4)Inapoi\n");
           scanf("%d",&optiune2);
           if(optiune2>4) 
           {printf("\x1b[31moptiune invalida\x1b[0m\x1b[1m\n");sleep(1);goto Inceput_Meniu;}
           switch(optiune2)
           {
            case 1:
                system("clear");
                afisare_din_lista(v,n);
                actualizare(v,n);
                printf("\n\x1b[32mFlota Actualizata\x1b[0m\x1b[1m\n");
                sleep(1);
                system("clear");
                goto ACT;
                break;
            case 2:
                system("clear");
                afisare_din_lista(v,n);
                adaugare(v,n);
                n+=1;
                sleep(1);
                system("clear");
                goto ACT;
                break;
            case 3:
                system("clear");
                afisare_din_lista(v,n);
                stergere(v,n);
                printf("\n\x1b[32mMasina Stearsa\x1b[0m\x1b[1m\n");
                n-=1;
                sleep(1);
                system("clear");
                goto ACT;
                break;
            case 4:
                goto Inceput_Meniu;
                break;
           }
        case 2:
            system("clear");
            int y=cautare(v,n);
            if(y<n)
                printf("\n\n\x1b[32mMasina Cautata se Afla pe Pozitia/Indexul \x1b[34m%d\x1b[0m\x1b[1m\n",y);
            else
                printf("\x1b[31mNu exista in flota masina cautata\x1b[0m\x1b[1m\n");
            sleep(3);
            system("clear");
            goto Inceput_Meniu;
            break;
        case 3:
            system("clear");
            afisare_din_lista(v,n);
            printf("1) Inapoi\n");
            int g;
            scanf("%d",&g);
            goto Inceput_Meniu;
            break;
        case 4:
            REZ:
            system("clear");
            n2=initializeaza_lista_fara_header(r,"rezervare.txt");
            printf("\x1b[34mFlota de Masini\x1b[0m\x1b[1m\n\n");
            afisare_din_lista(v,n);
            FILE *fp= fopen("rezervare.txt","r");
            int c = fgetc(fp);
            if (c != EOF)
            {    printf("\x1b[34mRezervare Curenta\x1b[0m\x1b[1m\n");
                afisare_din_lista(r,n2);}
            else
                 printf("\x1b[31mMomentan nu exista masina rezervata\x1b[0m\x1b[1m\n");
            printf("\n\n1)Rezerva o Masina\n2)Anuleaza Rezervarea\n3)Inapoi\n");
            scanf("%d",&optiune2);
            if(optiune2>2) 
            {printf("optiune invalida");sleep(1);goto Inceput_Meniu;}
            switch(optiune2)
            {
                case 1:
                    rezerva(v,n,&ocupata);
                    //printf("\n\x1b[32mRezervare Realizata\n\x1b[0m\x1b[1m");
                    v[ocupata].disponibil=0;
                    sleep(1);
                    system("clear");
                    goto REZ;
                    break;
                case 2:
                    anuleaza();
                    printf("\n\x1b[32mRezervare Anulata\x1b[0m\x1b[1m\n");
                    v[ocupata].disponibil=1;
                    sleep(1);
                    system("clear");
                    goto REZ;
                    break;
                case 3:
                    goto Inceput_Meniu;
                    break;
            }
        case 5:
            salveaza(v,n);
            printf("\n\x1b[0\x1b[32msalvat\x1b[0m\x1b[1m\n\n");
            sleep(1);
            goto Inceput_Meniu;
            break;
        case 6:
            goto end;
            break;
            
    }
    end: return 0;
}