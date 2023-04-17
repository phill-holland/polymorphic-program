#include "score.h"

void polymorphic::score::clear()
{
    for(int i = 0; i < scores.size(); ++i)
    {
        scores[i] = 0.0f;
    }
}

void polymorphic::score::compute(std::string value)
{
    auto occurances = [](std::string to_find, std::string value) 
	{ 
		int result = 0;
		int idx = 0;

        for(int i = 0; i < value.size(); ++i)
        {
			if(value[i] == to_find[idx]) 
			{
				++idx;
				if(idx >= to_find.size())
				{
					idx = 0;
					++result;
				}
			}
			else idx = 0;
        }

        return result;
	};

	auto first_position = [](std::string to_find, std::string value) 
	{ 
		int idx = 0;

        for(int i = 0; i < value.size(); ++i)
        {
			if(value[i] == to_find[idx]) 
			{
				++idx;
				if(idx >= to_find.size())
				{
					return (int)(i - (to_find.size()-1));					
				}
			}
			else idx = 0;
        }

        return -1;
	};

    clear();

    if(value.size() > 0)
	{		
      	const int a_len = 6;
        const std::string alphabet[] = { "he", "ll", "o ", "wo", "rl", "d!" };
        const int position[] = { 0, 2, 4, 6, 8, 10 };

		std::string comp("hello world!");
		int l1 = comp.size();
		int l2 = value.size();
			
		int d = abs(l2 - l1);
		if(d > 50) d = 50;
		scores[0] = ((d / 50.0f) * -1.0f) + 1.0f;

// ***
for(int i = 0; i < a_len - 1; ++i)
{
	//int o = occurances(alphabet[i], value);
	int f1 = first_position(alphabet[i], value);
	int f2 = first_position(alphabet[i+1], value);

	int idx = (i * 2) + 1;

	if(f1 < f2)//&&(f1 == position[i]))
	{
		float distance = (float)abs(f1 - f2);
		scores[idx + 1] = ((distance / 10.0f) * -1.0f) + 1.0f;
		//dis_score = ((distance / 10.0f) * -1.0f) + 1.0f;
	}
	else scores[idx + 1] = 0.0f;

		//int j = first_position(alphabet[i], value);
	
	/*
	int o = occurances(alphabet[i], value);						        
	if(o > 0)
	{
		scores[idx] = 1.0f /(float)o;
	}
	else scores[idx] = 0.0f;
	*/
//scores[idx] = 1.0f;
	//scores[idx] = 1.0f;// occ_score;// * penalty;
	//scores[idx + 1] = dis_score;// * penalty;
/*
	for(int j = i + 1; j < a_len; ++j)
	{
		int f2 = first_position(alphabet[j], value);
		float distance = (float)abs((f1 - f2) / 2);
		dis_score = ((distance / 10.0f) * -1.0f) + 1.0f;
	}*/
	/*
	float score = 0.0f;

	if((o==0)&&(j == position[i]))
	{
		for(int j = 0; j < value.size(); j += 2)
		{

		}
	}*/
}

for(int i = 0; i < a_len; ++i)
{	
	int f1 = first_position(alphabet[i], value);
	int idx = (i * 2) + 1;
	if(f1 == position[i]) scores[idx] = 1.0f;
	else scores[idx] = 0.0f;
	/*
	int f1 = first_position(alphabet[i], value);
	int o = occurances(alphabet[i], value);						        
	int idx = (i * 2) + 1;

	if(o == 1)
	{
		
		float distance = (float)abs(f1 - position[i]);
		scores[idx] = ((distance / 10.0f) * -1.0f) + 1.0f;
	} else scores[idx] = 0.0f;
	*/
}
// ***

/*		int run = 0;
		int max_run = 0;

//value = std::string("hello world!");
		for(int i = 0; i < a_len; ++i)
		{
            float occ_score = 0.0f;            
            float dis_score = 0.0f;            
			//float penalty = 1.0f;
			
			int o = occurances(alphabet[i], value);						        
            if(o > 0)
            {
                occ_score = 1.0f /(float)o;

                int j = first_position(alphabet[i], value);
                float distance = (float)abs(j - position[i]);
                dis_score = ((distance / 10.0f) * -1.0f) + 1.0f;

				if((o == 1)&&(j == position[i])) 
				{ 
					++run;
				}
				else 
				{
					dis_score = 0.0f;
					if(run > max_run) max_run = run;
					run = 0;
					//penalty = 0.80f;
				}

				//dis_score *= occ_score;
                //if(j == position[i]) dis_score = 1.0f;
				//else dis_score /= 2.0f;
            }

            int idx = (i * 2) + 1;
			
            scores[idx] = 1.0f;// occ_score;// * penalty;
            scores[idx + 1] = dis_score;// * penalty;
		}

		if(run > max_run) max_run = run;
		float m = ((float)run) / ((float)a_len);
		scores[0] = 1.0f;//m;
*/
		//scores[0] *= m;
    }
}


float polymorphic::score::sum()
{
    float result = 0.0f;

    for(int i = 0; i < scores.size(); ++i)
    {
        result += scores[i];
    }
    
    return result / ((float)scores.size());
}