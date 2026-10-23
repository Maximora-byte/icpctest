<a id="开发审查与密钥流程"></a>
# 开发、审查与密钥流程 / Development, Review, and Credentials Workflow

<a id="本仓适用范围"></a>
## 本仓适用范围 / Scope in This Repository

当前仓库是独立 C++ 练习与学习笔记；逐文件编译方式见 [README](../README.md#快速开始)。默认分支仅保留自动标签工作流文件，没有统一测试、Codecov 或图片专用工作流。

This repository contains independent C++ exercises and learning notes; see the [README](../README.md#快速开始) for per-file compilation. The default branch retains only the auto-label workflow file, not a unified testing, Codecov, or image-specific workflow.

下文的外部服务与密钥流程是条件性协作约定，不表示本仓已经配置这些服务，也不构成启用服务或修改密钥的授权。

The external-service and credential procedures below are conditional collaboration agreements. They do not indicate that these services are configured in this repository or authorize enabling services or changing credentials.

```text
需求 → 本地分支 / Copilot Student → PR → 本地检查结果 → 人工审核
                                      └→ matchall-bot 分类
图片优化（如适用）→ ImgBot PR → 实际配置的检查 → 人工审核
Doppler → dev: 本地应用 / ci: 专用测试 / prd: 经授权的服务器
```

English flow: requirements → local branch / Copilot Student → PR → local check results → human review, with matchall-bot classification. Image optimization, if applicable: ImgBot PR → actually configured checks → human review. Doppler: dev for local applications, ci for dedicated tests, and prd for authorized servers.

<a id="日常使用"></a>
## 日常使用 / Everyday Workflow

1. 明确需求、验收条件和允许修改的组件；如仓库或上级目录存在 AGENTS.md，先读取相关说明。<br>
   Define the requirements, acceptance criteria, and components that may change; read applicable AGENTS.md instructions in the repository or parent directories first, if present.
2. 在独立分支实现；Copilot Student 使用当前支持的 Auto 模型。给提示词提供源码与合成测试数据，不提供密钥、用户数据或生产日志。<br>
   Implement on an isolated branch; use the currently supported Auto model for Copilot Student. Provide source code and synthetic test data in prompts, not credentials, user data, or production logs.
3. 本地执行当前项目的必要检查：使用对应语言工具链编译并运行受影响的题解，验证题目样例及相关边界情况。不要为每种语言建立测试矩阵，也不要运行无关题解。<br>
   Run the necessary local project checks: compile/run the affected solution with the language toolchain, problem samples, and relevant boundary cases. Do not add a matrix for every language or run unrelated solutions.
4. 创建小范围 PR，说明行为、检查结果、迁移和回滚影响。如以后另行配置 CI，应按实际工作流说明检查范围；不要把标签工作流当作编译或测试证明。<br>
   Create a focused PR describing behavior, check results, migration, and rollback impact. If CI is configured later, state its scope according to the actual workflows; do not treat labeling as proof of compilation or testing.
5. 人工代码 PR 准备好时，按需请求一次 Copilot review；普通图片、依赖和文档 bot PR 不默认请求。自动审查、每次 push 审查和付费超额默认关闭。<br>
   When a human code PR is ready, request Copilot review once if needed; do not request it by default for routine image, dependency, or documentation bot PRs. Automatic reviews, reviews on every push, and paid overage stay off by default.
6. 检查实际提交的本地验证结果后人工审核；只有已配置相应工作流时才检查 CI / Codecov。合并不触发生产部署许可。<br>
   Review manually after inspecting local validation results for the actual commit; check CI / Codecov only when the corresponding workflows are configured. Merging does not authorize production deployment.

<a id="doppler-local"></a>
## Doppler 本地应用 / Doppler Local

默认继续使用既有的无密钥检查。如果受影响后端需要凭据，为该服务建立独立的 Doppler project，以及使用合成或沙盒凭据的 dev config，然后运行 `doppler run --project <service> --config dev -- <application-command>`。不要使用共享的全服务 token，不要用该命令包裹 IDE、Copilot CLI 或代理。浏览器、Android 和小程序构建只接收有意公开的配置；签名及账户凭据属于独立发布操作。

Existing secret-free checks remain the default. If an affected backend needs credentials, create a separate Doppler project for that service and a dev config with synthetic or sandbox credentials, then use `doppler run --project <service> --config dev -- <application-command>`. Do not use one shared all-service token. Do not wrap an IDE, Copilot CLI or agent in this command. Browser/Android/mini-program builds receive only intentionally public configuration; signing and account credentials are separate release operations.

<a id="doppler-github-actions"></a>
## Doppler GitHub Actions 集成 / Doppler GitHub Actions

普通 PR 单元测试不需要真实密钥。需要联网集成测试时，使用独立 `ci` 环境、只读 service account 和 OIDC 短期身份，仅允许受信任默认分支的手动 workflow_dispatch。绑定准确 repository、ref、event_name、workflow_ref、audience 和 environment subject；禁止通配仓库权限、pull_request_target 执行 PR 代码、fork 或任意分支取密钥。

Ordinary PR unit tests do not need real credentials. Networked integration tests require a separate `ci` environment, a read-only service account, and short-lived OIDC identity, limited to manual workflow_dispatch on the trusted default branch. Bind the exact repository, ref, event_name, workflow_ref, audience, and environment subject; prohibit wildcard repository access, executing PR code under pull_request_target, and credential retrieval by forks or arbitrary branches.

只把 OIDC identity ID 放到 GitHub variable；不存长期 Doppler token。不导出所有 GitHub secrets，不把 prd 同步到 Actions、Codespaces 或 Copilot Agents。取密钥的 job 不安装或执行 PR 提供的依赖/脚本，不写环境到日志或 artifact。接入前应为本仓另行提供可访问的配置说明与明确授权；本仓未提供 Doppler CI 工作流。

Store only the OIDC identity ID in a GitHub variable, not a long-lived Doppler token. Do not export all GitHub secrets or synchronize prd to Actions, Codespaces, or Copilot Agents. Credential-fetching jobs must not install or run PR-provided dependencies/scripts or write environment values to logs or artifacts. Before integration, provide accessible configuration instructions and explicit authorization for this repository; no Doppler CI workflow is provided here.

<a id="doppler-server"></a>
## Doppler 服务器 / Doppler Server

每个服务各有 prd 配置及只读单配置 token。token 存在该服务专属的受保护凭据文件，不能给容器、Copilot 或其他服务。生产迁移先审批明确的变量清单和目标，再备份、验证、暂存新配置、检查、仅重建该服务并验证健康；保留已知良好的旧配置以便回滚。Doppler 断网或配置无效时终止刷新，正在运行的服务继续使用原配置；不启用 watch/定时重启。

Each service has its own prd configuration and read-only, single-configuration token. Keep the token in that service's protected credential file, unavailable to containers, Copilot, or other services. Before a production migration, approve the exact variables and destination; then back up, validate, stage and check the new configuration, rebuild only that service, and verify health. Retain the known-good old configuration for rollback. Abort refresh if Doppler is unavailable or the configuration is invalid; running services continue with the original configuration. Do not enable watch mode or scheduled restarts.

GitHub App 私钥、现有账户 OAuth refresh tokens、数据库、聊天数据和备份不在本次迁移范围。生产密钥变更需要单独审批，不能把整台服务器的 .env 自动上传。

GitHub App private keys, existing account OAuth refresh tokens, databases, chat data, and backups are outside this migration's scope. Production credential changes require separate approval; never automatically upload the entire server's .env.

<a id="额度与分工"></a>
## 额度与分工 / Quotas and Responsibilities

matchall-bot 不消耗 Actions 贴标签额度；旧 auto-label workflow 保持禁用。ImgBot 只在已选择的图片仓库工作。若另行配置 Codecov，应复用已有测试并避免重复上传；当前本仓没有覆盖率上传配置。Copilot 使用学生包含额度，额外预算保持 $0；Doppler 使用已生效的学生 Team 权益，不开启收费附加项。

matchall-bot does not consume Actions quota for labeling; the old auto-label workflow stays disabled. ImgBot works only in selected image repositories. If Codecov is configured separately, reuse existing tests and avoid duplicate uploads; this repository currently has no coverage-upload configuration. Copilot uses the included student quota, with extra spending kept at $0; Doppler uses the active student Team benefits without paid add-ons.
