void stop() // Causes a segmentation fault
{
    int *nullPointer = nullptr;
    *nullPointer = 10;
}


void loop() // Causes a infinite loop
{
    while (true)
    {
        ;
    }
}