#include <stdio.h>

#define comedy 1
#define tragedy 0

/******定义话剧结构体*******/
typedef struct{
    char name[15];		/* 话剧名 */
    int type;			/* 话剧类型 */
}Drama;

/******定义表演结构体*******/
typedef struct{
    char name[15];		/* 话剧名 */
    int audience;		/* 观众人数 */  
}Performance;
  
/******定义账单结构体*******/
typedef struct{
    char* Customer_Name;	/* 顾客姓名 */
    Performance perf[3];	/* 顾客观看话剧数据 */
}Bill;

 
/*************函数声明**************/
void Print_Bill(Bill Bigco, Drama plays[3])
{
    /* 定义总金额 */
    int totalamount = 0;
    
    /* 定义金额 */
    int thisamount = 0;
    
    /* 定义积分 */
    int VolumeCredits = 0;

    int i = 0;
  
    for(i = 0; i < 3; i++)
    {
	switch (plays[i].type)
	{
		 case tragedy:
        	{
                	thisamount = 40000;
                	if (Bigco.perf[i].audience > 30)
                	{
                    		thisamount += 1000 * (Bigco.perf[i].audience - 30);
                	}
         	}       
		break;
            
		case comedy:
		{
               		thisamount = 30000;
                	if (Bigco.perf[i].audience > 20)
                	{
                    		thisamount += 10000 + 500 * (Bigco.perf[i].audience - 20);
                	}
                	thisamount += 300 * Bigco.perf[i].audience;
        	}      
        break;
	
		default:
			return;
		                
        }
    	VolumeCredits += ((Bigco.perf[i].audience - 30 > 0) ? Bigco.perf[i].audience - 30 : 0);
        
    	/*向下取整*/
    	if (comedy == plays[i].type)
    	{
       		VolumeCredits += Bigco.perf[i].audience / 5; 
    	}
    
        totalamount += thisamount;
        
        /*打印每种话剧的明细*/
        printf("	%s:$%d (%d seats)\r\n", plays[i].name, thisamount/100, Bigco.perf[i].audience);  
        
    }
    
    /*打印积分和花费*/
    printf("Amount owed is $%d\r\n", totalamount/100);
    printf("You earned %d credits\r\n", VolumeCredits);
}

int main()
{

    /*初始化三种话剧*/
    Drama plays[3] = {{"Hamlet", 0}, {"As You Like It", 1}, {"Othello", 0}};
    
    /*初始化三种表演*/
    Performance performances[3] = {{"Hamlet", 55}, {"As You Like It", 35}, {"Othello", 40}};
    
    /*初始化Bigco的账单结构体*/
    Bill Bigco = {"Bigco", {performances[0], performances[1], performances[2]}};
    
    printf("Print_Bill for %s\r\n", Bigco.Customer_Name);

    /*调用函数*/
    Print_Bill(Bigco, plays);
    
    return 0;
}
