
float arm_kP=.5, arm_kI=.5, arm_kD=.5;
float drive_kP=.5, drive_kI=.5, driver_kD=.5;
float arm_errorSum=0, arm_lastError=0;


float Update(float goal, float currentValue) {
  float error = goal - currentValue;
  float p = *kP_ * error;
  errorSum_ += error;
  float i = *kI_ * errorSum_;
  float dError = error - lastError_;
  float d = *kD_ * dError;
  lastError_ = error;
  return p + i + d;
}
