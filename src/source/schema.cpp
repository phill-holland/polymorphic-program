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
}

polymorphic::schema polymorphic::schema::cross(schema &value)
{
    program p = data.cross(data, value.data);
    return schema(p);
}

void polymorphic::schema::run()
{
    std::string output = data.run();
    _score = compare(output, "hello world!");
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
