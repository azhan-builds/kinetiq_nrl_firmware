#include "NRL.h"
#include <math.h>

static HexaDCMotor leftMotor
{
    { .dirPin = MOTOR_L_DIR, .pwmPin = MOTOR_L_PWM }
};

static HexaDCMotor rightMotor
{
    { .dirPin = MOTOR_R_DIR, .pwmPin = MOTOR_R_PWM, .flipped = true }
};

static HexaServo arm
{
    { .signalPin = SERVO_1, .startAngle = 90.0f }
};

static HexaServo gripper
{
    { .signalPin = SERVO_2, .startAngle = 15.0f }
};

static TankDrive drive(leftMotor, rightMotor);

class ShaazTeleOP : public NRLOpMode {
public:
    void init() override 
    {
        leftMotor.begin();
        rightMotor.begin();
        arm.begin();
        gripper.begin();
    }

    void loop() override 
    {
        drive.drive(-gamepad1.leftY(), gamepad1.leftX());
        
        float stickY = gamepad1.rightY();
        if (stickY > 0.20f)
        {
            arm.setPosition(0);
        }

        else if (stickY < -0.20f)
        {
            arm.setPosition(90);
        }

        else
        {
            arm.setPosition(90);
        }

        if (gamepad1.justPressed(BTN_Y)) 
        {
            gripper.setPosition(80.0f); 
        }

        if (gamepad1.justPressed(BTN_X))
        {
            gripper.setPosition(145.0f);
        }
    }

    void stop() override 
    {
        drive.stop();
        arm.detach();
        gripper.detach();
    }
};

REGISTER_OPMODE(ShaazTeleOP, "Kinetiq", TELEOP);