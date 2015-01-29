#include<stdio.h>
#include<math.h>
#include<string.h>


/*Function defined swap number*/
void Swap(int *s,int i,int j)
{

int k;
k=s[i];
s[i]=s[j];
s[j]=k;
}



/*Function to get probable code word*/

int simulatedresolved(unsigned char IV[3],int Key[5],int Keybyte,int Codebyte)
{
int i,s[256],j,Index,Resolved,rotate,consta;
int k[8];
j=0;
k[0]=IV[0];
k[1]=IV[1];
k[2]=IV[2];
k[3]=Key[0];
k[4]=Key[1];
k[5]=Key[2];
k[6]=Key[3];
k[7]=Key[4];
for(i=0;i<=255;i++)
{
  	s[i]=i;
}


for(i=0;i<=(Keybyte+2);i++)
{
	consta=i%8;
	rotate=k[consta];
	j=j+s[i]+rotate;
	j=j%256;
	Swap(s,i,j);
}

if((s[0]==k[0])||(s[1]==0))
{
for(i=0;i<=255;i++)
{
	if(s[i]==Codebyte)
	{
		Index=i;
	}
}

Resolved=Index-j-s[Keybyte+3];
Resolved=Resolved%256;
if(Resolved<0)
{
	Resolved=Resolved+256;
}

return Resolved;
}
else
{
return -1;
}
}



/*Function to get index of maximum entry in the Array*/

int maximumcount(int array[5][256],int row)
{
    unsigned int i,j,k;
	j=0;
	for(i=0;i<=255;i++)
	{
		if((array[row][i])>j)
		{
			j=array[row][i];
			k=i;
		}
	}
return k;
}





int main(int argc, char *argv[] )
	{
		unsigned int counter,k,m,Codebyte,i,temp,KeyByte;
		int reading;
		unsigned char stringg[4];
		unsigned char kk;
		unsigned char codee;
		unsigned int kk1;
		int count[5][256];
		unsigned int Key[5];
		unsigned char IV[4];
		Key[0]=0;
		Key[1]=0;
		Key[2]=0;
		Key[3]=0;
		Key[4]=0;
		/*Initializing the two dimentional counter array to 0 */
		for(counter=0;counter<=4;counter++)
		{
		for(k=0; k<=255 ;k++)
		{
			count[counter][k]=0;
		}
		}
		
		for(KeyByte=0;KeyByte<=4;KeyByte++)
		{
		FILE *ptr_myfile;
		ptr_myfile=fopen(argv[1],"rb");
		
		k=1;
		fseek(ptr_myfile,24,SEEK_SET);
			
		do
		{
		reading=fread(&stringg,1,4,ptr_myfile);
		k=stringg[0]-3;
		
		
		if(k==KeyByte)
		{
			IV[0]=stringg[0];
			IV[1]=stringg[1];
			IV[2]=stringg[2];
			
			codee=stringg[3]^'C';
			Codebyte=codee;
					
			
			m=simulatedresolved(IV,Key,k,codee);
			
			if(m!=-1)
			{
			count[k][m]=count[k][m]+1;
			}
			
			
			
		}
		
		
		
		fseek(ptr_myfile,139,SEEK_CUR);
		
		}while((reading !=0 ));
		
		Key[KeyByte]=maximumcount(count,KeyByte);
		fclose(ptr_myfile);
		
		}
		
		for(i=0;i<=4;i++)
		{
		printf("%c",Key[i]);
		}
		printf("\n");
		
		
		return 0;
	}

