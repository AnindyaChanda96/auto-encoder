/*----------------------------------------------MULTI-LAYERED PERCEPTRONS----------------------------------------------------------
-----------------------------------SINGLE HIDDEN LAYER:BACK-PROPAGATION ALGORITHM IN C++-----------------------------------------*/

// HEADER FILES.
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<fstream>

using namespace std;


float sigmoid_calc_return(float x)
    {
        x=(1/(1+exp(-x)));
        return x;
    }


int main()
{
    srand(time(NULL));

    // VARIABLES.
    float input_layer_i[3];
    float desired_output_k[3];

    float tolerance;
    float eta;

    float net_input_hidden_node[2];
    float net_output_hidden_node[2];

    float net_input_output_node[3];
    float net_output_output_node[3];

    float net_error;

    float w1[3][2];
    float w2[2][3];
    float bias_neurons_weight[2];

    float delta_k[3];
    float delta_j[2];

    float error_total;

    int i,j,k,l,n,p,temp=0,r;

    // ARCHITECTURE.

    eta=0.1;
    cout<<endl<<"ENTER THE VALUE OF LEARNING RATE(ETA) : "<<eta;

    cout<<endl<<"10000 ITERATIONS PER TRAINING DATA SET";
    int iterations = 10000;

    cout<<endl<<"ENTER RADIUS OF SPHERE : ";
    cin>>r;

    cout<<endl<<"ENTER THE NUMBER OF DATA SETS FOR LEARNING PROCESS : 900";


    // GENERATING RANDOM VALUES OF WEIGHTS AMONG -0.5 AND 0.5.

    for(i=0;i<3;i++)
        {
        for(j=0;j<2;j++)
            {
            w1[i][j]=((float) rand()) / (float) RAND_MAX;
            }
        }

    for(j=0;j<2;j++)
        {
         for(k=0;k<3;k++)
            {
            w2[j][k]=((float) rand()) / (float) RAND_MAX;
            }
        }
    for(l=0;l<2;l++)
    {
        bias_neurons_weight[l]=((float) rand()) / (float) RAND_MAX;
    }

    ifstream infile;
    infile.open("SphereLearnSet.txt");
    infile.seekg(0);

    ifstream infile1;
    infile1.open("SphereTestSet.txt");
    infile1.seekg(0);

    ofstream outfile;
    outfile.open("LearningDataPlot2D.txt",ios::trunc);

    ofstream outfile1;
    outfile1.open("TestingDataPlot2D.txt",ios::trunc);

    ofstream outfile2;
    outfile2.open("OutputLearningPoints.txt",ios::trunc);

    ofstream outfile3;
    outfile3.open("OutputTestPoints.txt",ios::trunc);

    //LEARNING DATA

    for(p=0;p<900;p++)
    {

       for(i=0;i<3;i++)
       {
           infile>>input_layer_i[i];
           input_layer_i[i]/=r;
       }

    //ASSIGNING EQUAL VALUES AT INPUT OF INPUT LAYER AND OUTPUT OF OUTPUT LAYER NODES FOR AUTO-ENCODER.

        for(l=0;l<3;l++)
        {
        desired_output_k[l]=input_layer_i[l];
        }

    //CALCULATING NET INPUT & OUTPUT AT ALL NODES
    for(l=0;l<iterations;l++)
    {

   for(j=0;j<2;j++)
        {
        net_input_hidden_node[j]=0;
            for(i=0;i<3;i++)
                {
                 net_input_hidden_node[j]+=input_layer_i[i]*w1[i][j];           // NET INPUT TO THE NODES AT HIDDEN LAYER.
                }

        net_output_hidden_node[j]=sigmoid_calc_return(net_input_hidden_node[j]+bias_neurons_weight[0]);// OUTPUT OF THE NODES AT HIDDEN LAYER.

        }

        for(k=0;k<3;k++)
        {
        net_input_output_node[k]=0;
            for(j=0;j<2;j++)
                {
                 net_input_output_node[k]+=net_output_hidden_node[j]*w2[j][k];   // NET INPUT TO THE NODES AT O/P LAYER.
                }

        net_output_output_node[k]=sigmoid_calc_return(net_input_output_node[k]+bias_neurons_weight[1]); // OUTPUT OF THE NODES AT O/P LAYER.

        }
    //FINDING DELTA K

    for(k=0;k<3;k++)
    {
        delta_k[k]=(net_output_output_node[k]-desired_output_k[k])*(net_output_output_node[k])*(1-net_output_output_node[k]);
    }

    //FINDING DELTA J
    for(j=0;j<2;j++)
    {
        temp=0;
        for(k=0;k<3;k++)
        {
            temp+=delta_k[k]*w2[j][k];
        }
        delta_j[j]=net_output_hidden_node[j]*(1-net_output_hidden_node[j])*temp;
    }
if(l==0)
{
    error_total=0;

    for(k=0;k<3;k++)
    {
    error_total+=(0.5)*pow((net_output_output_node[k]-desired_output_k[k]),2);
    }

    cout<<endl<<"ERROR TOTAL FOR DATA SET "<<p+1<<" BEFORE UPDATING : "<<error_total;
    error_total=0;
}


        //UPDATING WEIGHTS.

        for(j=0;j<2;j++)
        {
                for(k=0;k<3;k++)
                {
                    w2[j][k]+=(-1)*eta*delta_k[k]*net_output_hidden_node[j];
                }

        }

        for(i=0;i<3;i++)
        {
                for(j=0;j<2;j++)
                {
                    w1[i][j]+=(-1)*eta*input_layer_i[i]*delta_j[j];
                }
        }
    }

    //RECALCULATING AFTER WEIGHT UPDATES.

    for(j=0;j<2;j++)
        {
        net_input_hidden_node[j]=0;
            for(i=0;i<3;i++)
                {
                 net_input_hidden_node[j]+=input_layer_i[i]*w1[i][j];           // NET INPUT TO THE NODES AT HIDDEN LAYER.
                }
        net_output_hidden_node[j]=sigmoid_calc_return(net_input_hidden_node[j]+bias_neurons_weight[0]);// OUTPUT OF THE NODES AT HIDDEN LAYER.
        outfile<<net_output_hidden_node[j]*r<<" ";
        }
        outfile<<endl;


        for(k=0;k<3;k++)
        {
        net_input_output_node[k]=0;
            for(j=0;j<2;j++)
                {
                 net_input_output_node[k]+=net_output_hidden_node[j]*w2[j][k];   // NET INPUT TO THE NODES AT O/P LAYER.
                }
        net_output_output_node[k]=sigmoid_calc_return(net_input_output_node[k]+bias_neurons_weight[1]); // OUTPUT OF THE NODES AT O/P LAYER.
        outfile2<<net_output_output_node[k]*r<<" ";
        }
        outfile2<<endl;

    error_total=0;

    for(k=0;k<3;k++)
    {
    error_total+=(0.5)*pow((net_output_output_node[k]-desired_output_k[k]),2);
    }

    cout<<endl<<"ERROR TOTAL FOR DATA SET "<<p+1<<" AFTER UPDATING : "<<error_total<<endl;
    error_total=0;
}

//TESTING DATA

 for(p=0;p<100;p++)
    {

       for(i=0;i<3;i++)
       {
           infile1>>input_layer_i[i];
           input_layer_i[i]/=r;
       }


    for(j=0;j<2;j++)
        {
        net_input_hidden_node[j]=0;
            for(i=0;i<3;i++)
                {
                 net_input_hidden_node[j]+=input_layer_i[i]*w1[i][j];           // NET INPUT TO THE NODES AT HIDDEN LAYER.
                }
        net_output_hidden_node[j]=sigmoid_calc_return(net_input_hidden_node[j]+bias_neurons_weight[0]);// OUTPUT OF THE NODES AT HIDDEN LAYER.
        outfile1<<net_output_hidden_node[j]*r<<" ";
        }
        outfile1<<endl;


        for(k=0;k<3;k++)
        {
        net_input_output_node[k]=0;
            for(j=0;j<2;j++)
                {
                 net_input_output_node[k]+=net_output_hidden_node[j]*w2[j][k];   // NET INPUT TO THE NODES AT O/P LAYER.
                }
        net_output_output_node[k]=sigmoid_calc_return(net_input_output_node[k]+bias_neurons_weight[1]); // OUTPUT OF THE NODES AT O/P LAYER.
         outfile3<<net_output_output_node[k]*r<<" ";
        }
        outfile3<<endl;

}

return 0;

}


