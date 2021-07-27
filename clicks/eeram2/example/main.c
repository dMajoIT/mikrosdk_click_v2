/*!
 * \file 
 * \brief Eeram2 Click example
 * 
 * # Description
 * This example demonstrates the use of EERAM 2 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and enables the click board.
 * 
 * ## Application Task  
 * Writes a desired number of bytes to the memory and then verifies if it is written correctly
 * by reading from the same memory location and displaying its content on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eeram2.h"

// ------------------------------------------------------------------ VARIABLES

static eeram2_t eeram2;
static log_t logger;

static char demo_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
static char read_data[ 9 ];
static uint8_t check_status;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeram2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    eeram2_cfg_setup( &cfg );
    EERAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeram2_init( &eeram2, &cfg );

    eeram2_set_on_hold_status( &eeram2, EERAM2_HOLD_DISABLE );
    Delay_ms( 100 );

    eeram2_set_write_status( &eeram2, EERAM2_WRITE_ENABLE );
    Delay_ms( 100 );
}

void application_task ( void )
{
    check_status = eeram2_write_continuous( &eeram2, 0x00543210, &demo_data[ 0 ], 9 );

    if ( check_status == EERAM2_ERROR )
    {
        log_printf( &logger, "   ERROR Writing    \r\n" );
        log_printf( &logger, "--------------------\r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "     Writing...     \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 100 );

    check_status = eeram2_read_continuous( &eeram2, 0x00543210, &read_data[ 0 ], 9 );

    if ( check_status == EERAM2_ERROR )
    {
        log_printf( &logger, "   Reading ERROR    \r\n" );
        log_printf( &logger, "--------------------\r\n" );
        for ( ; ; );
    }

    log_printf( &logger, " Read data : %s", read_data );
    log_printf( &logger, "--------------------\r\n" );
    
    Delay_ms( 1000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
