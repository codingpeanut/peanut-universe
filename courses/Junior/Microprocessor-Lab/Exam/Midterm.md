# 微處理機實驗期中考
## 第一題

`main.c` from `EXIT.c -> HAL_GPIO_EXTI_Callback()`
```c
if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)) {  // PC13 down
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
} else {
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}
```

`Timer_PWM.ioc`
- Button
```
GPIO -> PC13 -> User Label -> B1
```
- Timer 3
```
Prescaler 42000-1
Counter Peroid 6000-1
Pulse 2000
```

## 第二題

`main.c` from `Timer_PWM.c -> main()`
```c

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    uint16_t i;
    /*tim3 LED1*/
    for(i=0;i<1000;i++)
    {
        htim3.Instance->CCR3 = i;
        __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, i);
        HAL_Delay(1);
    }
    for(i=1000;i>=1;i--)
    {
        htim3.Instance->CCR3 = i;
        __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, i);
        HAL_Delay(1);
    }
    HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
}
```

`Timer_PWM.ioc`
- Button
```
GPIO -> PC13 -> NVIC -> Enable
```
- Interrupt Priority 
```
NVIC -> EXTI line[15:10] interrupts -> Enable 
NVIC -> EXTI line[15:10] interrupts -> Preemption Priority -> 2 (數字越小，優先級越高)
```
