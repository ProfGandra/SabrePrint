# Sabre 3D — Estado compartilhado e acesso multicliente

**Status:** requisito aprovado para implementação futura. Ainda não implementado no firmware ou no protótipo GitHub Pages.

## Princípio

O ESP32-S3 é a **única fonte de verdade** do estado da impressora. Navegadores são clientes de visualização e comando; **não mantêm impressões independentes**.

## Comportamento obrigatório

1. Ao conectar, qualquer navegador consulta o estado atual e mostra a impressão já em andamento, se houver.
2. Exibir arquivo atual, estado (ocioso, preparando, imprimindo, pausado, concluído, erro), progresso, temperaturas e conexão USB.
3. Atualizar clientes conectados em tempo real, sem recarregar a página.
4. Bloquear no **servidor** tentativas de iniciar outra impressão quando já existe trabalho ativo, independentemente do estado dos botões no navegador.
5. Desconexão de celular/computador não interrompe trabalho já armazenado no microSD e executado pelo ESP32.
6. Reconexão de cliente recupera estado atual do ESP32.
7. Comandos de pausa, retomada e cancelamento devem ser serializados e validados no servidor, com política de autorização a definir.
8. Se o ESP32 reiniciar ou perder energia, **não presumir retomada segura** da impressão; tratar recuperação separadamente.

## Arquitetura prevista

- `GET /api/status`: snapshot do estado, incluindo ID do trabalho, arquivo, progresso, temperaturas, conexão, timestamp/contador de versão.
- WebSocket (ou SSE): eventos de mudança de estado, progresso e telemetria.
- Endpoints de controle: comandos validados pelo ESP32, com respostas de conflito (por exemplo, HTTP 409) quando o estado não permite a ação.
- Um único gerenciador de trabalho e uma fila serial de transmissão G-code, sincronizados no firmware.
- Upload ao microSD separado do comando de iniciar impressão.
- Reconexão: consultar snapshot novamente antes de aceitar comandos.

## GitHub Pages

O protótipo web é **simulação local em cada navegador** e não representa estado compartilhado. Não exibir a simulação como se fosse telemetria real.

## Política pendente

Definir se todos os clientes podem pausar/cancelar ou se haverá operador principal e clientes somente leitura. Em qualquer caso, o bloqueio de trabalhos simultâneos é obrigatório.

Desenvolvido por DGandra - 2026.
