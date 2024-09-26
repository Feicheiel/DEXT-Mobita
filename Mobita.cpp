#include "Mobita.h"

Mobita::Mobita(
    const uint8_t& _PWM_A, const uint8_t& _PWM_B, const uint8_t& _PWM_C, const uint8_t& _PWM_D, 
    const uint8_t& _AF, const uint8_t& _AB, const uint8_t& _BF, const uint8_t& _BB,
    const uint8_t& _CF, const uint8_t& _CB, const uint8_t& _DF, const uint8_t& _DB
)
        : PWM_Pin_A (_PWM_A), PWM_Pin_B (_PWM_B), PWM_Pin_C (_PWM_C), PWM_Pin_D (_PWM_D), 
          AF (_AF), AB (_AB), BF (_BF), BB (_BB), CF (_CF), CB (_CB), DF (_DF), DB (_DB)
{
    pinMode(PWM_Pin_A, OUTPUT); pinMode(PWM_Pin_B, OUTPUT); pinMode(PWM_Pin_C, OUTPUT); pinMode(PWM_Pin_D, OUTPUT);
    pinMode(AF, OUTPUT); pinMode(BF, OUTPUT); pinMode(CF, OUTPUT); pinMode(DF, OUTPUT);
    pinMode(AB, OUTPUT); pinMode(BB, OUTPUT); pinMode(CB, OUTPUT); pinMode(DB, OUTPUT);

    Mobita::MotorA.pwm_pin = &PWM_Pin_A; Mobita::MotorA.fwd = &AF; Mobita::MotorA.bck = &AB;
    Mobita::MotorB.pwm_pin = &PWM_Pin_B; Mobita::MotorB.fwd = &BF; Mobita::MotorB.bck = &BB;
    Mobita::MotorC.pwm_pin = &PWM_Pin_C; Mobita::MotorC.fwd = &CF; Mobita::MotorC.bck = &CB;
    Mobita::MotorD.pwm_pin = &PWM_Pin_D; Mobita::MotorD.fwd = &DF; Mobita::MotorD.bck = &DB;

    // active HIGH is OFF, LOW is ON.
    digitalWrite(MotorA.fwd, MotorA.fwd_dir); digitalWrite(MotorA.bck, MotorA.bck_dir);
    digitalWrite(MotorB.fwd, MotorB.fwd_dir); digitalWrite(MotorB.bck, MotorA.bck_dir);
    digitalWrite(MotorC.fwd, MotorC.fwd_dir); digitalWrite(MotorC.bck, MotorA.bck_dir);
    digitalWrite(MotorD.fwd, MotorD.fwd_dir); digitalWrite(MotorD.bck, MotorA.bck_dir);
}

Mobita::~Mobita() {
    Mobita::MotorA.pwm_pin = nullptr; Mobita::MotorA.fwd = nullptr; Mobita::MotorA.bck = nullptr;
    Mobita::MotorB.pwm_pin = nullptr; Mobita::MotorB.fwd = nullptr; Mobita::MotorB.bck = nullptr;
    Mobita::MotorC.pwm_pin = nullptr; Mobita::MotorC.fwd = nullptr; Mobita::MotorC.bck = nullptr;
    Mobita::MotorD.pwm_pin = nullptr; Mobita::MotorD.fwd = nullptr; Mobita::MotorD.bck = nullptr;
}

void Mobita::softstart(Motor m1, Motor m2, Motor m3, Motor m4){
    if (Mobita::PWM_All) {
        uint16_t delay_ms = 333/PWM_All + ((333/PWM_All)? 1 : 0);
        for (uint8_t pwm = 1; pwm <= PWM_All; pwm++){
            if (m1.pwm_pin) {analogWrite(m1.pwm_pin, pwm); m1.isInMotion = true;}
            if (m2.pwm_pin) {analogWrite(m2.pwm_pin, pwm); m2.isInMotion = true;}
            if (m3.pwm_pin) {analogWrite(m3.pwm_pin, pwm); m3.isInMotion = true;}
            if (m4.pwm_pin) {analogWrite(m4.pwm_pin, pwm); m4.isInMotion = true;}

            delay(delay_ms)
        }
    }
}

void Mobita::softstop(Motor m1, Motor m2, Motor m3, Motor m4){
    if (Mobita::PWM_All) {
        uint16_t delay_ms = 133/PWM_All + ((133/PWM_All)? 1 : 0);
        for (int16_t pwm = PWM_All; pwm >= 0; pwm--){
            if (m1.pwm_pin) {analogWrite(m1.pwm_pin, pwm); m1.isInMotion = false;}
            if (m2.pwm_pin) {analogWrite(m2.pwm_pin, pwm); m2.isInMotion = false;}
            if (m3.pwm_pin) {analogWrite(m3.pwm_pin, pwm); m3.isInMotion = false;}
            if (m4.pwm_pin) {analogWrite(m4.pwm_pin, pwm); m4.isInMotion = false;}

            delay(delay_ms)
        }
    }
}

void Mobita::moveMotorBackward(Motor m1, Motor m2, Motor m3, Motor m4){
    if (Mobita::PWM_All){
        if (m1.pwm_pin) {
            // turn fwd ON (LOW) and turn bck OFF (HIGH).
            m1.setDir(0x1, 0x0);
        }
        if (m2.pwm_pin) {
            // turn fwd ON (LOW) and turn bck OFF (HIGH).
            m2.setDir(0x1, 0x0);
        }
        if (m3.pwm_pin) {
            // turn fwd ON (LOW) and turn bck OFF (HIGH).
            m3.setDir(0x1, 0x0);
        }
        if (m4.pwm_pin) {
            // turn fwd ON (LOW) and turn bck OFF (HIGH).
            m4.setDir(0x1, 0x0);
        }
    }
    // if the motor is already in motion stop it before reversing it.
    softstop((MotorA.isInMotion)? MotorA:defaultMotor, (MotorB.isInMotion)? MotorB:defaultMotor, (MotorC.isInMotion)? MotorC:defaultMotor, (MotorD.isInMotion)? MotorD:defaultMotor);

    softstart(m1, m2, m3, m4);
}

void Mobita::moveMotorForward(Motor m1, Motor m2, Motor m3, Motor m4){
    if (Mobita::PWM_All){
        if (m1.pwm_pin) {
            // turn fwd ON (LOW) and turn bck OFF (HIGH).
            m1.setDir(0x0, 0x1);
        }
        if (m2.pwm_pin) {
            // turn fwd ON (LOW) and turn bck OFF (HIGH).
            m2.setDir(0x0, 0x1);
        }
        if (m3.pwm_pin) {
            // turn fwd ON (LOW) and turn bck OFF (HIGH).
            m3.setDir(0x0, 0x1);
        }
        if (m4.pwm_pin) {
            // turn fwd ON (LOW) and turn bck OFF (HIGH).
            m4.setDir(0x0, 0x1);
        }
    }
    softstart(m1, m2, m3, m4);
}

void Mobita::brake(){
    softstop(MotorA, MotorB, MotorC, MotorD);
}

void Mobita::setPWM(const uint8_t& pwm) {
    PWM_All = pwm;
}

void Mobita::mobitaForward() {
    moveMotorForward(MotorA, MotorB, MotorC, MotorD);
}

void Mobita::mobitaBackward() {
    moveMotorBackward(MotorA, MotorB, MotorC, MotorD);
}

void Mobita::mobitaLeft() {
    // Left side FWD Right side BCK
    leftSideForward();
    rightSideBackward();
}

void Mobita::mobitaRight(){
    // Right side FWD Left side BCK
    rightSideForward();
    leftSideBackward();
}

void Mobita::leftSideForward() {
    moveMotorForward(MotorA, MotorB, defaultMotor, defaultMotor);
}

void Mobita::leftSideBackward() {
    moveMotorBackward(MotorA, MotorB, defaultMotor, defaultMotor)
}

void Mobita::rightSideForward() {
    moveMotorForward(defaultMotor, defaultMotor, MotorC, MotorD);
}

void Mobita::rightSideBackward() {
    moveMotorBackward(defaultMotor, defaultMotor, MotorC, MotorD);
}

void Mobita::trailingDiagonalBackward(){
    moveMotorBackward(MotorA, defaultMotor, defaultMotor, MotorD);
}

void Mobita::trailingDiagonalForward(){
    moveMotorForward(MotorA, defaultMotor, defaultMotor, MotorD);
}

void Mobita::leadingDiagonalBackward(){
    moveMotorBackward(defaultMotor, MotorB, MotorC, defaultMotor);
}

void Mobita::leadingDiagonalForward(){
    moveMotorForward(defaultMotor, MotorB, MotorC, defaultMotor);
}

void motorABackward(){
    moveMotorBackward(MotorA, defaultMotor, defaultMotor, defaultMotor);
}

void motorAForward(){
    moveMotorForward(MotorA, defaultMotor, defaultMotor, defaultMotor);
}

void motorBBackward(){
    moveMotorBackward(defaultMotor, MotorB, defaultMotor, defaultMotor);
}

void motorBForward(){
    moveMotorForward(defaultMotor, MotorB, defaultMotor, defaultMotor);
}

void motorCBackward(){
    moveMotorBackward(defaultMotor, MotorC, defaultMotor, defaultMotor);
}

void motorCForward(){
    moveMotorForward(defaultMotor, MotorC, defaultMotor, defaultMotor);
}

void motorDBackward(){
    moveMotorBackward(defaultMotor, MotorD, defaultMotor, defaultMotor);
}

void motorDForward(){
    moveMotorForward(defaultMotor, MotorD, defaultMotor, defaultMotor);
}

const String getMobitaState(){
    String state = String(PWM_All) + ';';
    state += ((!MotorA.fwd_dir) && (MotorA.bck_dir)) ? "F;" : ((MotorA.fwd_dir) && (!MotorA.bck_dir)) ? "B;" :"U;";
    state += ((!MotorB.fwd_dir) && (MotorB.bck_dir)) ? "F;" : ((MotorB.fwd_dir) && (!MotorB.bck_dir)) ? "B;" :"U;";
    state += ((!MotorC.fwd_dir) && (MotorC.bck_dir)) ? "F;" : ((MotorC.fwd_dir) && (!MotorC.bck_dir)) ? "B;" :"U;";
    state += ((!MotorD.fwd_dir) && (MotorD.bck_dir)) ? "F;" : ((MotorD.fwd_dir) && (!MotorD.bck_dir)) ? "B;" :"U;";

    return state;
}