# Sabre 3D — Autenticação e permissões

**Status:** arquitetura aprovada; implementação pendente.

## Modelo de acesso

O ESP32-S3 opera em SoftAP `Sabre3D` e serve a interface em `http://192.168.4.1`.

| Permissão | Visitante (sem login) | Operador (autenticado) |
|---|---|---|
| Visualizar estado, temperaturas e progresso | Sim | Sim |
| Visualizar nome do arquivo em impressão | Sim | Sim |
| Enviar G-code ao microSD | Não | Sim |
| Iniciar impressão | Não | Sim |
| Pausar, retomar e cancelar | Não | Sim |
| Movimentar eixos / aquecer | Não | Sim |
| Enviar comandos pelo terminal | Não | Sim |
| Alterar configurações | Não | A definir; preferencialmente administrador |

## Requisitos de segurança

- A autorização é **validada no firmware em cada endpoint e comando WebSocket**, nunca apenas ocultando botões na interface.
- A senha do operador não deve ser gravada em texto puro no firmware ou no repositório. Armazenar derivação criptográfica com sal; definir credencial inicial individual ou provisionamento local.
- Sessões com token aleatório de curta duração, expiração por inatividade e opção de sair. Invalidar sessões após troca de senha.
- Proteger contra tentativas repetidas de login com limitação de taxa e atraso progressivo.
- O SoftAP deve usar WPA2 e senha de rede própria, distinta da senha do operador.
- **Atenção:** HTTP sem TLS em Wi-Fi local não protege as credenciais de um atacante que tenha acesso à rede. A implantação precisa avaliar HTTPS ou outro mecanismo seguro de autenticação antes de operar impressoras reais; WPA2 não substitui a proteção da sessão.
- Dados sensíveis (senhas/tokens) nunca devem aparecer em logs, URLs ou arquivos de interface estática.
- A parada de emergência e as proteções térmicas devem existir independentemente da autenticação web.

## Estado compartilhado

Todos os visitantes e operadores recebem o mesmo estado do trabalho atual. Somente operadores autenticados podem alterá-lo. O servidor rejeita tentativa de iniciar um segundo trabalho enquanto houver impressão ativa.

## Interface

- Ao abrir: painel em modo **visualização**.
- Botão **Entrar** abre autenticação de operador.
- Após login: habilitar controles autorizados e indicar **Operador conectado**.
- Botão **Sair** retorna ao modo visualização.
- Se a sessão expirar: bloquear imediatamente novos comandos e solicitar novo login, sem interromper uma impressão já em andamento.

## Pendências de implementação

Definir método de provisionamento e recuperação de senha, duração da sessão, política de múltiplos operadores e estratégia de proteção das credenciais no ambiente SoftAP.

Desenvolvido por DGandra - 2026.
