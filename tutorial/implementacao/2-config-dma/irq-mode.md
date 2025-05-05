
# Modo IRQ (Interrupção)

No modo IRQ, **o objetivo é executar uma função específica assim que uma transferência de dados é concluída.** Essa função é chamada de rotina de tratamento de interrupção (ISR). Primeiro, vamos importar a biblioteca para trabalhar com interrupções (`hardware/irq.h`) e definir uma variável que irá sinalizar a conclusão da transferência:

```c
#include "hardware/irq.h"

static volatile bool dma_complete = false;
```
> 🚩 Não esqueça de colocar a `hardware_irq` no `CMakeLists.txt` também, em `target_link_libraries`.

Ela será modificada pela função handler e verificada no loop principal do programa para podermos tratar os dados que foram transferidos (no nosso caso, apenas exibir eles). Agora sim podemos definir a função para tratar a interrupção:

```c
void dma_handler()
{
    // Limpa o flag de interrupção do DMA
     dma_channel_acknowledge_irq0(dma_channel);

    // Marca a transferência como concluída
    dma_complete = true;

    // Reinicia a transferência DMA para o próximo ciclo
    dma_channel_set_write_addr(dma_channel, (void *)adc_buffer, true);
}
```
- ` dma_channel_acknowledge_irq0(dma_channel)`: Limpa o flag de interrupção do DMA
- `dma_complete = true;`: Marca a transferência como concluída
- `dma_channel_set_write_addr(dma_channel, (void *)adc_buffer, true);`: Reinicia a transferência DMA
    > Essa linha redefine o endereço de escrita do canal DMA para o início do adc_buffer. Como o DMA já transferiu SAMPLES (20) amostras para o adc_buffer na transferência anterior, essa chamada sobrescreve o endereço de destino, fazendo o DMA começar a escrever novamente no início do adc_buffer na próxima transferência.

## 4) Iniciando a interrupção
Agora que já temos nossa função handler, podemos ativar nossa interrupção:

```c
dma_channel_set_irq0_enabled(dma_channel, true);
irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
irq_set_enabled(DMA_IRQ_0, true);
```
- Dizemos que queremos receber interrupções quando o dma desse canal (`dma_channel`) terminar de executar as transferências
- Dizemos qual função vai lidar com essa interrupção (`dma_handler`)
- Habilitamos a interrupção de fato (`irq_set_enabled`).

### O que é DMA_IRQ
DMA_IRQ é o mecanismo pelo qual **o controlador de DMA sinaliza ao processador que uma transferência foi concluída ou que precisa de atenção.** Isso elimina a necessidade de o processador verificar constantemente o status do DMA, otimizando o desempenho do sistema

No RP2040, existem `DMA_IRQ_0` e `DMA_IRQ_1`, ou seja, dois canais de interrupção disponíveis para colocar no DMA.

## Finalizando nossa main
---
```c
int main()
{
    stdio_init_all();
    initialize_adc();
    initialize_dma();

    // Loop principal
    while (true)
    {
        printf("\nDMA IRQ\n");
        if (dma_complete)
        {
            print_samples();      // Exibe as amostras
            dma_complete = false; // Reseta a flag
            sleep_ms(1000);     
        }
    }

    return 0;
}
```
- `if(dma_complete):` Verifica se a transferência foi concluída (flag ativada lá no handler)
   > Se sim, exibe os dados (`print_samples()`) e reseta a flag (`dma_complete = false;`)

Pronto, agora você já pode executar o programa e ver os dados capturados no terminal.

---
## 🔗 Veja o código fonte completo [AQUI](../../../src/dma_init/dma_irq.c)
---
## [Voltar](../../implementacao/2-config-dma/config-dma.md#4-modo-bloqueante-x-modo-com-interrupção)