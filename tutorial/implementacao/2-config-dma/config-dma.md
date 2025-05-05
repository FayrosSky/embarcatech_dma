# Configuração do DMA
A DMA no Raspberry Pi Pico oferece duas formas principais de operação: 

- Modo bloqueante (blocking)
- Modo com interrupções (IRQ)

Cada um desses modos tem características, vantagens e desvantagens específicas, que os tornam mais adequados para diferentes tipos de aplicações. Abaixo, vamos explorar cada um. Mas antes, vamos fazer a configuração que é universal para ambos os modos.

Antes de tudo, vamos importar a biblioteca `hardware/dma.h` que nos permite acessar as funções de configuração e controle do DMA.

```c
#include "hardware/dma.h"
```
> 🚩 Não esqueça de colocar ela no `CMakeLists.txt` também, em `target_link_libraries`.

Agora sim podemos começar a configuração...

## 1) Criando o objeto de configuração

1. Pegamos um canal DMA livre e definimos uma configuração padrão:
    ```c
    dma_channel = dma_claim_unused_channel(true);
    dma_channel_config config = dma_channel_get_default_config(dma_channel);
    ```
    O `dma_channel_get_default_config` traz uma estrutura de configuração padrão (Para ver cada campo, clique [AQUI](../../funcoes/configuracao.md#5-dma_channel_get_default_config-uint-channel))

    Isso facilita nossa vida porque já vem a maior parte configurada, mas podemos configurar cada parte de forma individual com funções próprias para isso. Cada parte da configuração pode ser alterada com funções `channel_config_set`. Exemplo:
    - `channel_config_set_read_increment();`
    - `channel_config_set_write_increment();`
    - `channel_config_set_dreq();`
    - ...

    > Veja a lista completa [aqui](https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#group_channel_config).

    Vamos fazer algumas modificações:
    ```c
    channel_config_set_transfer_data_size(&config, DMA_SIZE_16);
    channel_config_set_read_increment(&config, false);
    channel_config_set_write_increment(&config, true);
    channel_config_set_dreq(&config, DREQ_ADC);
    ```
    - Colocamos o tamanho do dado para 16 bits, que é o padrão na leitura de temperatura (`DMA_SIZE_16`)
    - Definimos que o endereço de leitura não deve avançar (`FALSE`), já que vamos pegar do mesmo local
    - Definimos que o endereço de escrita deve avançar (`TRUE`)
        > Isso é necessário porque vamos armazenar em um buffer, onde vai guardar todas as amostras para serem tratadas depois
    - Colocamos que o DREQ seja o ADC (`DREQ_ADC`)
        > No caso, estamos dizendo que o sinal do ADC será o gatilho que avisa o DMA para transferir dados. Ou seja, estamos conectando com o ADC!

    ### Outros exemplos de DRQ
    Exemplos de sinais que podem ativar a transferência do DMA são: 

    | Sinal DREQ         | Uso Típico                                                                 |
    |--------------------|-----------------------------------------------------------------------------|
    | `DREQ_ADC`         | Captura de sinais analógicos, como sensores de temperatura ou microfones. |
    | `DREQ_SPI0_TX`     | Envio de dados para dispositivos SPI, como displays ou sensores.           |
    | `DREQ_UART0_RX`    | Recepção de dados de módulos como Bluetooth ou GPS.                        |
    | `DREQ_PWM_WRAP0`   | Sincronização de eventos com o fim de ciclos PWM.                          |
    | `DREQ_TIMER0`      | Transferência de dados com base em temporização precisa.                   |

## 2) Associando a configuração com o canal
Para configurar nosso canal, utilizaremos a função `dma_channel_configure()`. Mas antes, vamos definir um número de amostras que vão ser captadas até o DMA "gritar" e também o buffer onde será enviado os dados captados:
```c
#define SAMPLES 20     // Número de amostras por transferência DMA
static volatile uint16_t adc_buffer[SAMPLES]; // para onde vai as leituras
```

Agora vamos configurar de fato o canal:

```c
dma_channel_configure(
    dma_channel,        // Canal que queremos configurar
    &config,            // Configuração do DMA
    (void *)adc_buffer, // Endereço de escrita 
    &adc_hw->fifo,      // Endereço de leitura (FIFO do ADC)
    SAMPLES,            // Quantidade de transferências
    false               // Não inicia ainda
);
```
- `dma_channel`: Canal que queremos configurar
- `config`: Configuração que queremos aplicar (nossa `config`)
- `adc_buffer`: Endereço de escrita
    > Para onde vamos escrever os dados?
- `adc_hw->fifo`: Endereço de leitura
    > De onde estamos pegando os dados? Nesse caso é do FIFO do ADC, por isso estamos usando `&adc_hw->fifo`
- `SAMPLES`: Quantidade de transferências (até ativar a IRQ)
- `false`: Não inicia ainda (é nosso liga/desliga)
## 3) Exibindo os dados (tratamento)
Aqui no nosso projeto, vamos apenas exibir os dados capturados. Mas é aqui que você pode fazer o tratamento que quiser com os dados que foram coletados:

```c
int count = 0;

void print_samples()
{
    printf("DMA concluído! Amostras:\n");
    printf("Número da amostragem: %d\n", count++);
    for (int i = 0; i < SAMPLES; i++)
    {
        float voltage = adc_buffer[i] * 3.3f / (1 << 12);
        float temp = 27 - (voltage - 0.706) / 0.001721;
        printf("Amostra %d: %.2f°C\n", i, temp);
    }
    printf("\n");
}
```
> O que estamos fazendo aqui é percorrendo o buffer `adc_buffer` e imprimir os valores de cada amostra, convertendo eles para o valor de temperatura em °C.
## 4) Modo bloqueante x Modo com Interrupção
Agora que já temos a função que vai exibir os dados capturados, é aqui que vamos terminar a configuração do nosso DMA, em umas das duas formas:

- ### [4.1 Modo bloqueante](./blocking-mode.md)
- ### [4.2 Modo com interrupção](./irq-mode.md)

---
## [Voltar](../../../READme.md#4-criando-nosso-projeto-com-dma)