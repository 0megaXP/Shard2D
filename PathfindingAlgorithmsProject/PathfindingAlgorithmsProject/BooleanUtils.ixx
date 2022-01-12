module;

export module BooleanUtils;

export bool Between(const double& value,const double& a, const double& b, bool extremes = true)
{
	if (a > b)
		return (value <= (extremes ? a : a - 1) && value >= (extremes ? b : b + 1));
	else
		return (value <= (extremes ? b : b - 1) && value >= (extremes ? a : a + 1));

};