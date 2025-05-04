#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "hardware/irq.h"

#define SAMPLES 20     // Número de amostras por transferência DMA
#define TEMP_CHANNEL 4 // Canal 4 para o sensor de temperatura interno

// Variáveis globais
static int dma_channel;
static volatile uint16_t adc_buffer[SAMPLES];

int count = 0;

// Inicializa o ADC
void initialize_adc()
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(TEMP_CHANNEL);

    // Configura o FIFO do ADC
    adc_fifo_setup(
        true,  // Habilita FIFO
        true,  // Habilita requisição DMA
        1,     // Threshold de 1 amostra (DMA é chamado a cada amostra)
        false, // Sem erro
        false  // Sem shift (12 bits)
    );

    // Inicia o ADC em modo contínuo
    adc_run(true);
}

// Inicializa o DMA
void initialize_dma()
{
    dma_channel = dma_claim_unused_channel(true);
    dma_channel_config config = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&config, DMA_SIZE_16);
    channel_config_set_read_increment(&config, false);
    channel_config_set_write_increment(&config, true);
    channel_config_set_dreq(&config, DREQ_ADC);

    // Configura o canal DMA
    dma_channel_configure(
        dma_channel,        // Canal que queremos configurar
        &config,            // Configuração do DMA
        (void *)adc_buffer, // Endereço de escrita
        &adc_hw->fifo,      // Endereço de leitura (FIFO do ADC)
        SAMPLES,            // Quantidade de transferências
        false               // Não inicia ainda
    );

    // Inicia a primeira transferência
    dma_channel_start(dma_channel);
}

// Função para exibir as amostras
void print_samples()
{
    printf("DMA concluído!\n");
    printf("Número da amostragem: %d\n", count++);
    for (int i = 0; i < SAMPLES; i++)
    {
        float voltage = adc_buffer[i] * 3.3f / (1 << 12);
        float temp = 27 - (voltage - 0.706) / 0.001721;
        printf("Amostra %d: %.2f°C\n", i, temp);
    }
    printf("\n");
}

void await_dma_complete()
{
    // Espera a transferência terminar
    dma_channel_wait_for_finish_blocking(dma_channel);

    // Exibe as amostras
    print_samples();

    // Reinicia a transferência
    dma_channel_set_write_addr(dma_channel, (void *)adc_buffer, true);
}

// Função principal
int main()
{
    stdio_init_all();
    initialize_adc();
    initialize_dma();

    // Loop principal
    while (true)
    {
        printf("\nDMA Blocking\n");
        await_dma_complete();
        sleep_ms(1000);
    }

    return 0;
}