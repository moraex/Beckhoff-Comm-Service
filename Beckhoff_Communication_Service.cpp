#include "Beckhoff_Communication_Service.h"

/******************* beckhoff_connection ********************
*************************************************************
Operation: Perform connection between Toradex and Beckoff
Input Parameters: 
Output: 
*/

using namespace std;

volatile int wck;
char IOMap[4096];
int expectedWck;

// constructor method that performs the initial configurations before apply
// the connections between toradex - beckhoff.
// in the future, we can make the module positions dinamic
//
//
Beckhoff_Communication_Service::Beckhoff_Communication_Service()
{
    strcpy(remota.networkBoardName, NETW_BOARD_NAME);
    
    remota.terminalPositionIn = 2;
    strcpy(remota.beckhoffInputModuleName, DIGITAL_INPUT_MODULE);

    remota.terminalPositionOut = 3;
    strcpy(remota.beckhoffOutupModuleName, DIGITAL_OUTPUT_MODULE);

    remota.terminalPositionAnalog = 4;
    strcpy(remota.beckhoffAnalogModuleName, ANALOG_MODULE);

    cout << "SUCCESSFULLY BUILT!" << endl;
};

//
//
//
Beckhoff_Communication_Service::~Beckhoff_Communication_Service()
{
    // ? free variables
};


//
//
// return:  1 (success)
//          2 (network card problems)
//          3 (slaves problems)
//          4 (cards problems)
int Beckhoff_Communication_Service::beckhoff_connect()
{
    // consider replace this if by a try-catch
    if(ec_init(remota.networkBoardName)){

        // wouldn't if (ec_config_init(FALSE)) produce de same result?
        if(ec_config_init(FALSE) > 0){

            // verifying each module...
            if(strcmp(ec_slave[1].name, ACOPLADOR)){
                cout << "error finding card "
                     << remota.beckhoffOutupModuleName
                     << endl;
                return 4;
            }

            if(strcmp(ec_slave[remota.terminalPositionIn].name, DIGITAL_INPUT_MODULE)){
                cout << "error finding card "
                     << remota.beckhoffOutupModuleName
                     << endl;
                return 4;
            }

            if(strcmp(ec_slave[remota.terminalPositionOut].name, DIGITAL_OUTPUT_MODULE)){
                cout << "error finding card "
                     << remota.beckhoffOutupModuleName
                     << endl;
                return 4;
            }

            if(strcmp(ec_slave[remota.terminalPositionAnalog].name, ANALOG_MODULE)){
                cout << "error finding card "
                     << remota.beckhoffAnalogModuleName
                     << endl;
                return 4;
            }
        
            // SUCCESS
            return 1;

        } else {
            return 3;
        }

    } else {
        // network board connection problem
        return 2;
    }

}


//
//
//
bool Beckhoff_Communication_Service::verify_communication_status()
{
    cout << "verify_communication_status okay" << endl;
    return true;
}

//
//
//
bool Beckhoff_Communication_Service::beckhoff_disconnect()
{
    try {
        // close ethercat communication socket
        ec_close();
        return true;

    } catch (int err) {
        cout << err << endl;
        return false;
    }
    
}

void read_digital_inputs()
{

}

//
//
//
bool write_digital_outputs()
{
    // SUCCESS
    return true;
}