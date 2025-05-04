# Configurando a dupla dinâmica: ADC + DMA
Como estamos realizando a leitura da temperatura, primeiro vamos configurar o ADC para capturar esses dados. Essa parte não tem a ver com o DMA, exceto com um trecho específico (que sinalizarei com ⭕).

1. Definimos o canal do sensor de temperatura interno (que é 4)
    ```c
    #define TEMP_CHANNEL 4 // Sensor de temperatura interno
    ```

2. Habilitamos o conversor ADC utilizando a fila

    ```c
    void initialize_adc()
    {
        // Inicializando o adc e sensor de temperatura
        adc_init();
        adc_set_temp_sensor_enabled(true);
        adc_select_input(TEMP_CHANNEL);

        // Configura o FIFO do ADC
        adc_fifo_setup(
            true,  
            true,  
            1,    
            false, 
            false  
        );

        // Inicia o ADC
        adc_run(true);
    }
    ```
    O `adc_fifo_setup()` é responsável por configurar o ADC para captar os dados e enviar para uma estrutura de Fila (FIFO). 
    
    No RP2040, a fila (FIFO) guarda até 4 amostras.
    Essa função é estruturada assim:  `void adc_fifo_setup (bool en, bool dreq_en, uint16_t dreq_thresh, bool err_in_fifo, bool byte_shift)`
    - `en`: Habilita a FIFO
      > valor TRUE
    - `dreq_en`: Habilita a requisição DMA (o FIFO vai avisar o DMA quando tiver dados dentro dele pra serem transferidos) ⭕
      > valor TRUE
    - `dreq_thresh`: Threshold (Define a partir de quantos dados no FIFO o DMA ou a IRQ vai ser acionada. Por exemplo, se for 2, então toda vez que tiver 2 itens da fila vai acionar o DMA ou a interrupção)
      > valor 1
    - `err_in_fifo`: ativa/destiva a verificação de erro (Se for true, o bit 15 de cada valor no FIFO indica se houve erro na conversão)
      > valor FALSE
    - `byte_shift`: Sem shift (Se for true, os dados do FIFO são enviados com apenas 1 byte de tamanho, em vez dos 2 bytes padrão. Útil quando você quer usar DMA pra mandar os dados pra buffers de bytes)
      > valor FALSE

Pronto, já estamos captando as amostras. Agora vamos seguir para a configuração do DMA.

## Por que do uso do ADC com FIFO?
O FIFO garante que os dados do ADC sejam armazenados temporariamente até que o DMA possa transferi-los, evitando que o buffer seja preenchido ou esvaziado antes que os dados possam ser processados, garantindo um fluxo contínuo de informações.

---
## 🔗 Trecho Completo

```c
#define TEMP_CHANNEL 4 // Canal 4 para o sensor de temperatura interno

// Inicialização do ADC
void initialize_adc()
  {
    // Inicializando o adc e sensor de temperatura
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(TEMP_CHANNEL);

    // Configura o FIFO do ADC
    adc_fifo_setup(
       true,  
       true,  
       1,    
       false, 
       false  
    );

    // Inicia o ADC
    adc_run(true);
  }
```

---
## [Voltar](../../../READme.md#4-criando-nosso-projeto-com-dma)