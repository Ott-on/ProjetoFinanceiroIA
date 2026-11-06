
# FinanceAssistant

Sistema de assistência financeira com integração a agentes de inteligência artificial.

## Objetivo

Desenvolver uma aplicação capaz de receber solicitações de usuários,
consultar informações financeiras e fornecer respostas contextualizadas
por meio de agentes de IA.

## Arquitetura

O projeto utiliza uma arquitetura modular, com as seguintes responsabilidades:

- **C++:** backend principal e regras de negócio.
- **OpenCode:** execução e orquestração dos agentes.
- **MCP:** integração com ferramentas e serviços externos.
- **BRAPI:** fonte de dados financeiros.
- **PostgreSQL:** armazenamento de usuários, perfis e sessões.
- **Telegram:** interface de comunicação com os usuários.

## Tecnologias

- C++20
- CMake
- Visual Studio 2022
- PostgreSQL
- Docker
- OpenCode Server
- Model Context Protocol (MCP)

## Estrutura do projeto

```text
FinanceAssistant/
├── src/
│   ├── Domain/
│   ├── Application/
│   ├── Infrastructure/
│   └── Presentation/
├── tests/
├── database/
├── opencode/
├── docker/
├── CMakeLists.txt
└── README.md
```

## Status

Em desenvolvimento — estrutura inicial do repositório.
