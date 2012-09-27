#define PID_H_

class Pid{
	public:

	Pid(double* kP_ = 0, double* kI = 0, double* kD = 0);

	void ResetError();

	double Update(double gaol, double curVal);

	private:

	double* kP_;
	double* kI_;
	double* kD_;

	double errorSum_;

	double lastError_;
};
