#include <iostream>
#include <string>
#include <vector>

float sigmoid(float sum)
{
    return(1 / (1 + exp(-sum)));
}

float sum(float in1, float in2, float in3, float we1, float we2, float we3, float bias)//takes in all the inputs and weights and sums it up
{
    return((in1*we1)+(in2*we2)+(in3*we3)+bias);
}

void print(std::vector <float> weights)
{
    bool done = false;
    int index = 0;

    while (done != true)
    {
        std::cout << weights[index] << "\n";
        index++;
        if (index == 20) { break; }
    }



}

std::vector <int> index (int neuron)
{
    if (neuron == 4) 
    {
        std::vector <int> output;
        output.push_back(0);
        output.push_back(3);
        output.push_back(6);
        output.push_back(15);
        return(output);
    }

    if (neuron == 5)
    {
        std::vector <int> output;
        output.push_back(1);
        output.push_back(4);
        output.push_back(7);
        output.push_back(16);
        return(output);
    }

    if (neuron == 6)
    {
        std::vector <int> output;
        output.push_back(2);
        output.push_back(5);
        output.push_back(8);
        output.push_back(17);
        return(output);
    }

    if (neuron == 7)
    {
        std::vector <int> output;
        output.push_back(9);
        output.push_back(11);
        output.push_back(13);
        output.push_back(18);
        return(output);
    }

    if (neuron == 8)
    {
        std::vector <int> output;
        output.push_back(10);
        output.push_back(12);
        output.push_back(14);
        output.push_back(19);

        return(output);
    }
}

float neuron(std::vector <float> package)
{
    float cont = sum(package[0], package[1], package[2], package[3], package[4], package[5], package[6]);
    return(sigmoid(cont));
    
}



float update(float weight, float input, float output, float target)
{
    float action = (0.01 * (target - output) * input);
    return(weight + action);
    
}

float error(float target, float output)
{
    return(target - output);

}

float updatex(float weight, float input, float error)
{
    float action = (0.10 * error * input);
    return(weight + action);

}

int main()
{
    int loops = 0;
    int generations;
    int input = 1;
    bool done = false;
    int Scount = 0;

    std::vector <float> weights{ 0.74, 0.13, 0.68, 0.80, 0.40, 0.10, 0.35, 0.97, 0.96, 0.35, 0.80, 0.50, 0.13, 0.90, 0.80, 0.90, 0.45, 0.36, 0.98, 0.92 };

    std::cout << "how many generations should the neural network run for?" << "\n";
    std::cin >> generations;

    float a = 0;
    float b = 0;
    float c = 0;
   
    int x;
    int y;

    float loss1 = 0;
    int loss1count = 0;

    while (loops != generations)
    {
        
        if (input == 7) { input = 1; }

        if (input == 1)
        {
            a = 0.50;
            b = 1.00;
            c = 0.75;
            
            x = 1;
            y = 0;
        }

        if (input == 2)
        {
            a = 1.00;
            b = 0.50;
            c = 0.75;
            
            x = 1;
            y = 0;
        }

        if (input == 3)
        {
            a = 1.00;
            b = 1.00;
            c = 1.00;
           
            x = 1;
            y = 0;
        }

        if (input == 4)
        {
            a = -0.01;
            b = 0.50;
            c = 0.25;
            
            x = 0;
            y = 1;
        }

        if (input == 5)
        {
            a = 0.50;
            b = -0.25;
            c = 0.13;
            
            x = 0;
            y = 1;
        }

        if (input == 6)
        {
            a = 0.01;
            b = 0.02;
            c = 0.05;
           
            x = 0;
            y = 1;
        }



        //forward

        //package layer 1
        int one = 0;
        int two = 3;
        int three = 6;
        int Pbias = 15;

        int oneA = 9;
        int twoA = 11;
        int threeA = 13;
        
        std::vector <float> layer1;
        for (int i = 0; i < 3; i++)
        {
            std::vector <float> package1{ a, b, c, weights[one], weights[two], weights[three], weights[Pbias]};
            layer1.push_back(neuron(package1));
            one++;
            two++;
            three++;
            Pbias++;
        }

        //package layer 2
        std::vector <float> layer2;
        for (int i = 0; i < 2; i++)
        {
            std::vector <float> package2{ layer1[0], layer1[1], layer1[2], weights[oneA], weights[twoA], weights[threeA], weights[Pbias]};
            layer2.push_back(neuron(package2));
            one++;
            two++;
            three++;
            Pbias++;
            
        }



        //backward
   
        std::vector <float> freshW;
        std::vector <float> freshB;
        float done = false;
        int layerindex;
        int count = 0;
        int neuron = 8;
        
        



      

        float target;

        float errorT = (error(y, layer2[1]) + error(x, layer2[0]));

        while (done != true)
        {
             if (neuron == 8) { layerindex = 1; } //layer index indicates/converts neuron's position in either layer1 or layer2 vector
            if (neuron == 7) { layerindex = 0; }
            if (neuron == 6) { layerindex = 2; }
            if (neuron == 5) { layerindex = 1; }
            if (neuron == 4) { layerindex = 0; }

            if (count < 2) //for layer 2
            {
                
                int valueA = 2;
                if (count == 0) { target = y; }
                if (count == 1) { target = x; }
                
                for (int i = 0; i < 3; i++) //for just one neuron do this for the amount of weights
                {
                    std::vector <int> located; 
                    located = index(neuron);  //put the desired neuron data into a vector
                 
                    int valueW = located[valueA];
                    float weight = weights[valueW];    //extract one of the weights from located weight is the value passed into the function

                    float in = layer1[valueA];                  //the sigmoid of previous neuron related to the weight above

                    loss1 += ((target - layer2[layerindex]) * (target - layer2[layerindex]));
                    loss1count++;
                    

                    if (loss1count == 100) 
                    { 
                        Scount++;
                        std::cout << (loss1/100) << " -- " << Scount << "\n";
                        loss1 = 0;
                        loss1count = 0;
                    }
                    
                    freshW.push_back(update(weight, in, layer2[layerindex], target));         //update the current weights
                    valueA--; 
                    
                    if (i == 1) //happens only once for the bias
                    {
                        freshB.push_back(update(weights[located[3]], 1, layer2[layerindex], target)); //last from index, 1, output of A8, A8's target
                        
                    }

                }
                    
            }

            if (count >= 2) //for layer 1. for the second layer the inputs and outputs shift in relation to the second layer
            {
                int valueB = 3; 

                for (int i = 0; i < 3; i++)
                {
                    std::vector <int> located = index(neuron);
                    float weight = weights[located[valueB]];

                    float in;
                    if (i == 0) { in = c; }
                    if (i == 1) { in = b; }
                    if (i == 2) 
                    { 
                        in = a; 
                        freshB.push_back(updatex(weights[located[3]], 1, errorT));
                    
                    }

                    freshW.push_back(updatex(weight, in, errorT));

                    valueB--;
                }

            }



            neuron--;
            count++;

            if (count == 5) { break; }

        }



        
        std::vector <float> atwork;
        

        int weight2a = 5;
        int weight2b = 2;
       
        int biasW = 4;

        int weight1a = 14;
        int weight1b = 11;
        int weight1c = 8;

        bool finished = false;

        while (finished != true)
        {
            atwork.push_back(freshW[weight1a]);
            atwork.push_back(freshW[weight1b]);
            atwork.push_back(freshW[weight1c]);
            
            weight1a--;
            weight1b--;
            weight1c--;

            if (weight1c == 5) { break; }

        }

        while (finished != true)
        {
            atwork.push_back(freshW[weight2a]);
            atwork.push_back(freshW[weight2b]);

            weight2a--;
            weight2b--;

            if (weight2b == -1) { break; }
        }

        while (finished != true)
        {
            atwork.push_back(freshB[biasW]);
            biasW--;

            if (biasW == -1) { break; }
        }

        weights = atwork;

      
     
        input++;
        loops++;
        


    }

    

}



