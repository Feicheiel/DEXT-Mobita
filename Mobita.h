#ifndef MOBITA_H
#define MOBITA_H

class Mobita {
  public:
  Mobita(const uint8_t& _PWM_A, const uint8_t& _PWM_B, const uint8_t& _PWM_C, const uint8_t& _PWM_D, 
         const uint8_t& _AF, const uint8_t& _AB, const uint8_t& _BF, const uint8_t& _BB,
         const uint8_t& _CF, const uint8_t& _CB, const uint8_t& _DF, const uint8_t& _DB);

  ~Mobita();

  void mobitaForward();
  void mobitaBackward();
  void mobitaLeft();
  void mobitaRight();

  void motorAForward();
  void motorABackward();
  void motorBForward();
  void motorBBackward();
  void motorCForward();
  void motorCBackward();
  void motorDForward();
  void motorDBackward();

  void leftSideForward();
  void leftSideBackward();
  void rightSideForward();
  void rightSideBackward();
  void leadingDiagonalForward();
  void leadingDiagonalBackward();
  void trailingDiagonalBackward();
  void trailingDiagonalForward();

  void brake();
  const String getMobitaState() const;
  void setPWM(const uint8_t& pwm);

  private:
  Mobita();
  Mobita(const Mobita*);
  Mobita(const Mobita&&);
  
  const uint8_t PWM_Pin_A, PWM_Pin_B, PWM_Pin_C, PWM_Pin_D, 
                AF, AB, BF, BB, CF, CB, DF, DB;
  
  uint8_t PWM_All {128}, PWM_A {0}, PWM_B {0}, PWM_C {0}, PWM_D {0};
  
  struct Motor {
       uint8_t *pwm_pin, *fwd, *bck, fwd_dir {0x1}, bck_dir {0x1};
       void setDir (const uint8_t& f, const uint8_t& b) {
              fwd_dir = f; bck_dir = b;
              digitalWrite(fwd, f); digitalWrite(bck, b);
       }
  } MotorA, MotorB, MotorC, MotorD, defaultMotor; 

  defaultMotor.pwm_pin = nullptr; defaultMotor.fwd = nullptr; defaultMotor.bck = nullptr; 

  void softstart(Motor m1, Motor m2, Motor m3, Motor m4);
  void softstop(Motor m1, Motor m2, Motor m3, Motor m4);
  void moveMotorForward(Motor m1, Motor m2, Motor m3, Motor m4);
  void moveMotorBackward(Motor m1, Motor m2, Motor m3, Motor m4);
}

#endif