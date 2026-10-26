# Firmware ESP32-S3 — Sabre 3D

## Teste inicial — v0.2.0-diag (ESP32-S3 CAM N16R8)

**Código-fonte de diagnóstico preparado, ainda não compilado ou testado em placa física.** Este teste não controla impressora, não inicializa USB Host, microSD nem câmera. Não conectar a impressora à porta USB-OTG nesta fase.

### Como gravar (PlatformIO / VS Code)

1. Instalar VS Code e extensão PlatformIO IDE.
2. Abrir a pasta `firmware/esp32` como projeto PlatformIO.
3. Conectar **USB-UART** da ESP32-S3 CAM ao computador com cabo de dados.
4. Executar **Build** e corrigir eventuais incompatibilidades de versões da plataforma/ESP-IDF antes de gravar.
5. Executar **Upload**; se necessário, usar sequência BOOT/RESET da placa.
6. Abrir **Monitor** a 115200 baud.

### Teste do Wi-Fi

- Rede: `Sabre3D`
- Senha **temporária de bancada**: `Sabre3D-Teste26` (está no código, **não serve para uso real**)
- Endereço: `http://192.168.4.1/`
- JSON: `http://192.168.4.1/api/diagnostico`
- O celular pode indicar “sem internet”; permanecer conectado ao Wi-Fi local.
- A tela mostra núcleos, revisão, Flash, PSRAM e heap livre. PSRAM com valor 0 significa que ela não foi disponibilizada ao firmware; pode exigir configuração adicional da placa e **não** significa necessariamente ausência física.
- A tela é propositalmente separada do painel de impressão web do repositório.

### Limites e cuidados

- Este projeto usa provisoriamente o alvo genérico `esp32-s3-devkitc-1`; confirmar pinagem, tipo de PSRAM, layout de Flash e modo de gravação da placa real.
- Não pressupor que o firmware funcione sem ajustes: **não foi compilado em CI nem validado no hardware**.
- **Não conectar a impressora ao USB-OTG antes de verificar VBUS de 5 V, alimentação, proteção contra retorno de corrente e esquema da placa.**
- **Não testar o microSD nem a câmera antes de identificar os pinos compartilhados.**
- Autenticação Master/Comum ainda não existe neste firmware; a rede de diagnóstico só deve ser usada em bancada isolada.
- Após validar esta etapa: testar microSD, depois USB Host sem impressora e, por fim, reconhecimento USB da controladora da impressora.

---

# Firmware ESP32-S3 — Sabre 3D

Área de desenvolvimento do firmware embarcado do Sabre 3D.

**Status: planejamento / não funcional.** Nenhum arquivo nesta pasta deve ser considerado firmware pronto para operar uma impressora.

## Objetivo

Hospedar a interface web na rede Wi-Fi local, receber G-code, armazená-lo no microSD e transmitir comandos por USB Host à controladora Marlin, com controle de fluxo e mecanismos de segurança.

## Estrutura

- `src/` — código-fonte C/C++ do firmware.
- `include/` — cabeçalhos e configurações.
- `lib/` — componentes próprios do projeto.
- `data/` — arquivos estáticos da interface web para servir no ESP32.
- `config/` — exemplos de configuração, sem credenciais reais.
- `test/` — testes automatizados e simuladores.
- `hardware/` — esquemas, pinagem e notas elétricas.

## Antes de implementar

1. Confirmar o modelo exato da placa ESP32-S3 e suas conexões USB Host, alimentação e microSD.
2. Ambiente definido: **PlatformIO com framework ESP-IDF**.
3. Validar a enumeração USB e o chipset USB-serial de cada impressora (CH340, CP210x, FTDI, CDC-ACM etc.).
4. Implementar comunicação Marlin com respostas `ok`, tratamento de `busy`/`Resend` e parada segura.
5. Validar proteção contra alimentação reversa USB, falhas térmicas e perda de comunicação.

**Importante:** a fonte 5 V do ESP32 será independente da impressora. O hardware USB Host precisa fornecer VBUS corretamente, sem retroalimentar o circuito.

## Identidade visual compartilhada

A interface web de referência fica na raiz do repositório (`/index.html`) e utiliza `/assets/capitao-dgandra.png` como carimbo de assinatura do Capitão DGandra, além de `/assets/sabre3d-logo.png`.

A interface destinada ao ESP32 deve preservar esses arquivos e seus caminhos relativos ao ser integrada ao servidor HTTP embarcado. A pasta `data/` é reservada para os recursos web do firmware; **a sincronização e o servidor web ainda não estão implementados**.

O modo de rede definido é **Wi-Fi SoftAP `Sabre3D`**, com acesso previsto por `http://192.168.4.1`. Não exige display ou roteador.

Desenvolvido por DGandra - 2026.
