
#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <rand.h>

void main_link()
{

    CRITICAL
    {
        add_SIO(nowait_int_handler); // disable waiting VRAM state before return
        set_interrupts(SIO_IFLAG);   // disable other interrupts
    }

    // puts("Host (A)");

    // puts("Connect (B)");

    // uint8_t mode = 0;

    // mode = waitpad(J_A | J_B | J_LEFT);
    // waitpadup();

    uint8_t connection_byte = 0;

    // printf("Waiting for connection...\n");
    // while (1)
    // {

    //     if (mode == J_A)
    //     {
    //         receive_byte();

    //         connection_byte = _io_in;

    //         if (connection_byte == 3)
    //         {
    //             break;
    //         }
    //     }
    //     else
    //     {
    //         _io_out = 3;
    //         send_byte();
    //         break;
    //     }
    // }

    // printf("Connection established");

    // Loop forever
    printf("Rock Paper Scissors\n");
    printf("UP - Rock\n");
    printf("Down - Paper\n");
    printf("Left - Scissors\n");
    uint8_t i = 0;
    uint8_t my_choice = 0;

    i = waitpad(J_UP | J_DOWN | J_LEFT);
    waitpadup();

    switch (i)
    {
    case J_UP:
        printf("Selected Rock\n");
        my_choice = 0;
        break;
    case J_DOWN:
        printf("Selected Paper\n");
        my_choice = 1;
        break;
    case J_LEFT:
        printf("Selected Sicsors\n");
        my_choice = 2;
        break;
    }

    _io_out = my_choice;
    send_byte();

    while (_io_status == IO_SENDING)
        ;

    receive_byte();

    while (_io_status == IO_RECEIVING)
        ;

    _io_out = my_choice;
    send_byte();

    connection_byte = _io_in;
    // printf("C: %d\n", connection_byte);

    if (connection_byte == my_choice)
    {
        printf("Draw!\n");
    }
    else if ((my_choice == 0 && connection_byte == 1) || (my_choice == 1 && connection_byte == 2) || (my_choice == 2 && connection_byte == 0))
    {
        printf("You lost :(\n");
    }
    else
    {
        printf("You won! :D\n");
    }

    // Game main loop processing goes here

    // Done processing, yield CPU and wait for start of next frame
    wait_vbl_done();
}

void main_cpu()
{
    // Loop forever
    printf("Rock Paper Sicsors\n");
    printf("UP - Rock\n");
    printf("Down - Paper\n");
    printf("Left - Sicsors\n");
    uint8_t i = 0;
    uint8_t my_choice = 0;
    uint16_t seed;

    while (1)
    {

        i = waitpad(J_UP | J_DOWN | J_LEFT);
        waitpadup();

        switch (i)
        {
        case J_UP:
            printf("You have selected Rock\n");
            my_choice = 0;
            break;
        case J_DOWN:
            printf("You have selected Paper\n");
            my_choice = 1;
            break;
        case J_LEFT:
            printf("You have selected Scissors\n");
            my_choice = 2;
            break;
        }

        seed = DIV_REG;

        initarand(seed);

        uint8_t random = rand() % 2;

        if (random == my_choice)
        {
            printf("Draw!\n");
        }
        else if ((my_choice == 0 && random == 1) || (my_choice == 1 && random == 2) || (my_choice == 2 && random == 0))
        {
            printf("You lost :(\n");
        }
        else
        {
            printf("You won! :D\n");
        }

        // Game main loop processing goes here

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}

void main(void)
{
    main_link();
}