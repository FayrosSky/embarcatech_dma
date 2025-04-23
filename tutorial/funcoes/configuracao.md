# Funções de Configuração DMA no Raspberry Pi Pico
## 1) `dma_channel_set_read_addr()`
  > Define de onde o canal DMA vai ler os dados (por exemplo, de uma região da memória ou de um periférico).
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_set_read_addr(uint channel, const volatile void * read_addr, bool trigger)`

   -   **Parâmetros:**

        -   `channel`: O número do canal DMA a ser configurado.
        -   `read_addr`: O endereço de memória ou periférico de onde o DMA lerá os dados.
        -   `trigger`: Uma variável booleana que indica se o DMA deve ser acionado imediatamente ou não.

  -   **Retorno:** Nenhum (void)
  </details>

---
## 2) `dma_channel_set_write_addr()`
  > Define para onde o canal DMA vai escrever os dados que ele leu.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_set_write_addr(uint channel, volatile void * write_addr, bool trigger)`

   -   **Parâmetros:**

        -   `channel`: O número do canal DMA a ser configurado.
        -   `write_addr`: O endereço de memória ou periférico para onde o DMA escreverá os dados.
        -   `trigger`: Uma variável booleana que indica se o DMA deve ser acionado imediatamente ou não.

  -   **Retorno:** Nenhum (void)
  </details>

---
## 3) `dma_channel_set_trans_count()`
  > Define quantas transferências (quantidade de dados) o canal DMA vai fazer.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_set_trans_count(uint channel, uint32_t trans_count, bool trigger)`

   -   **Parâmetros:**

        -   `channel`: O número do canal DMA a ser configurado.
        -   `count`: O número de transferências a serem realizadas.
        -   `trigger`: Uma variável booleana que indica se o DMA deve ser acionado imediatamente ou não.

  -   **Retorno:** Nenhum (void)
  </details>

---
## 4) `dma_channel_configure()`
  > Configura tudo de uma vez só — endereço de leitura, de escrita, quantidade de transferências e opções extras — e pode iniciar a transferência imediatamente.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `void dma_channel_configure(uint channel, const dma_channel_config * config, volatile void * write_addr, const volatile void * read_addr, uint transfer_count, bool trigger)`

   -   **Parâmetros:**

        -   `channel`: O número do canal DMA a ser configurado.
        -   `config`: Um ponteiro para uma estrutura `dma_channel_config` contendo os endereços de origem e destino e a contagem de transferências.
        -   `write_addr`: O endereço de memória ou periférico para onde o DMA escreverá os dados.
        -   `read_addr`: O endereço de memória ou periférico de onde o DMA lerá os dados.
        -   `transfer_count`: O número de transferências a serem realizadas.
        -   `trigger`: Uma variável booleana que indica se o DMA deve ser acionado imediatamente ou não.

  -   **Retorno:** Nenhum (void)
  </details>

---
## 5) `dma_channel_get_default_config (uint channel)`
  > Retorna uma estrutura `dma_channel_config` com as configurações padrão para um canal específico.
  <details>
  <summary>Ver detalhes</summary>

  - **Função completa:** `dma_channel_config dma_channel_get_default_config (uint channel)`

   -   **Parâmetros:**

        -   `channel`: O número do canal DMA para definir a configuração padrão.

  -   **Retorno:** Uma estrutura `dma_channel_config` contendo a configuração padrão para o canal especificado.

   ### ESTRUTURA PADRÃO

| Configuração         | Valor Padrão  | Explicação Simples                                                                 |
|----------------------|---------------|------------------------------------------------------------------------------------|
| **Read Increment**   | `true`        | Endereço de leitura avança a cada dado. Como ler um array.                        |
| **Write Increment**  | `false`       | Sempre escreve no mesmo lugar. Bom pra periféricos.                               |
| **DREQ**             | `DREQ_FORCE`  | DMA transfere sem esperar periférico.                                             |
| **Chain to**         | `self`        | Canal se encadeia com ele mesmo. 1️⃣                                                  |
| **Data size**        | `DMA_SIZE_32` | Transfere 32 bits (4 bytes) por vez.                                              |
| **Ring**             | `write=false, size=0` | Modo circular desligado. Endereços não se repetem.                     |
| **Byte Swap**        | `false`       | Não inverte os bytes. Dados seguem ordem normal. 2️⃣                                  |
| **Quiet IRQs**       | `false`       | Interrupções ativadas funcionam normalmente.                                      |
| **High Priority**    | `false`       | Canal sem prioridade especial. Espera a vez dele.                                 |
| **Channel Enable**   | `true`        | Canal já começa ativado após configuração.                                        |
| **Sniff Enable**     | `false`       | Sniffer desligado (não monitora conteúdo dos dados) 3️⃣                              |

---
 ### Explicação de algumas configurações "estranhas"
  - 1️⃣: A configuração "Chain to" define qual canal DMA será acionado automaticamente após a conclusão da transferência do canal atual. Por padrão, o canal se encadeia a si mesmo (`self`), permitindo operações contínuas.

    > No entanto, **um canal DMA pode acionar outro, criando sequências automáticas de transferências sem intervenção da CPU.**
        
- 2️⃣: Essencial para sistemas que usam diferentes ordens de bytes (Little Endian x Big Endian). Veja mais sobre esses termos [aqui](https://www.manualdocodigo.com.br/curso-assembly-snes-mega-parte43/).
- 3️⃣: Ativa/desativa o hardware de "sniffer" do DMA, que monitora os dados transferidos e realiza análises em tempo real para verificação de integridade de dados (como cálculos de checksums ou CRC).




  </details>



----
## [Voltar](../../READme.md#3-funções-associadas)  ----------------------------------------- Próx.: [Funções de Controle](./controle.md)	