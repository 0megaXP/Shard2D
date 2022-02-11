module;

export module BooleanUtils;

namespace Shard2D
{
	/**
	Return true if value is between a and b (in both ways)
		\param The value to compare
		\param The first edge value
		\param The second edge value
		\param Control if the extremes are valids
	*/
	export bool Between(const double& value, const double& a, const double& b, bool extremes = true)
	{
		if (a > b)
			return (value <= (extremes ? a : a - 1) && value >= (extremes ? b : b + 1));
		else
			return (value <= (extremes ? b : b - 1) && value >= (extremes ? a : a + 1));

	};
}