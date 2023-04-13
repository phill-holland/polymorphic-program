#include "schema.h"

std::mt19937_64 polymorphic::schema::generator(std::random_device{}());

void polymorphic::schema::reset()
{
    _score = 0.0f;
}

void polymorphic::schema::generate()
{
    data.clear();
    data.generate();
}

void polymorphic::schema::mutate()
{
	data.mutate();
}

polymorphic::schema polymorphic::schema::cross(schema &value)
{
    program p = data.cross(data, value.data);
    return schema(p);
}

std::string polymorphic::schema::run()
{
	_score = 0.0f;
	
    std::string output = data.run();
	if(output.size() > 0)
	{
		std::string comp("hello world!");
		int l1 = comp.size();
		int l2 = output.size();

		//if(l2 > l1)
		//{
			
			int d = abs(l2 - l1);
			if(d > 20) d = 20;
			_score = ((d / 20.0f) * -1.0f) + 1.0f;
			/*
			if(l2 > 0)
			{
				if(output[0] != 'h') _score *= (1.0f / ((float)l1));
			}
*/
			for(int i = 0; i < l1; ++i)
			{
				float penalty = 0.80f;
				if(i < l2)
				{
					if(output[i] == comp[i]) penalty = 1.0f;//_score *= (1.0f / ((float)l1));
				}

				_score *= penalty;
			}

			if(l2 > 0)
			{
				char previous = output[0];
				int cc = 0;
				for(int i = 1; i <l2; ++i)
				{
					if(output[i] == previous) ++cc;
					else cc = 0;

					previous = output[i];
				}

				if(cc >= 2)//l2 - 1)
				{
					 _score *= 0.20f;
				}
			}
			/*
			if(output.find(std::string("hel")) != std::string::npos) _score *= 0.25;
			if(output.find(std::string("lo  ")) != std::string::npos) _score *= 0.25;
			if(output.find(std::string("wor")) != std::string::npos) _score *= 0.25;
			if(output.find(std::string("ld!")) != std::string::npos) _score *= 0.25;
			
			if(output.find(std::string("hello")) != std::string::npos) _score *= 0.30;
			if(output.find(std::string("world!")) != std::string::npos) _score *= 0.30;
*/
/*
			int c = 0;
			int s = l1;
			if(l2 < l1) s = l2;
			for(int i = 0; i < s; ++i)
			{
				if(comp[i] == output[i]) ++c;
			}

			float tt = ((float)c)/((float)l1);
			_score *= tt;
			*/
		//}
    	//_score = compare(output, "hello world!");
		/*if(_score > 0.0f) 
		{
			std::string moo = "hello";
		}*/
	}

	return output;
}

float polymorphic::schema::compare(std::string left, std::string right)
{
	const int max = 64;
	int occurances[max];
	int position[max];

	for(int i=0; i < max; ++i)
	{
		occurances[i] = 0;
		position[i] = 0;
	}

	std::string condition, source;

	if(right.size() > left.size()) { condition = right; source = left; }
	else { condition = left; source = right; }

	int word_i = 0, word_j = 0;

	std::string a, b;

	for (long i = 0L; i < condition.size(); ++i)
	{
		char t1 = condition[i];

		if(t1 != ' ') a += t1;

		if(((t1 == ' ')||(i==condition.size() -1)&&(a.size() > 0L)))
		{
			word_j = 0;

			for(long j=0L; j < source.size(); ++j)
			{
				char t2 = source[j];

				if(t2 != ' ') b += t2;

				if(((t2 == ' ')||(j==source.size() -1)&&(b.size() > 0L)))
				{
					if((a.compare(b)==0)&&(word_i < max))
					{
						occurances[word_i]++;
						if(word_i == word_j) position[word_i] = 1;
					}

					++word_j;
					b.clear();
				}
			}

			a.clear();
			b.clear();

			++word_i;
		}
	}

	if(word_i <= 0 || word_j <= 0) return 0.0f;

	float result = 0.0f;

	for(int i=0;i<word_i;++i)
	{
		if(occurances[i] == 0) occurances[i] = word_j;
		else occurances[i] -= 1;

		float temp = ((float)occurances[i]);

		temp = ((temp / ((float)word_j)) * -1.0f) + 1.0f;
		temp = (temp * 0.5f) + (((float)position[i]) * 0.5f);

		result += temp;
	}

	return (result / ((float)word_i));
}
