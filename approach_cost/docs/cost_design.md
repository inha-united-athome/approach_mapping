# Cost Design

## 목적
이 패키지는 상호작용 접근 후보 셀들에 대해 공통 비용(`cost_common`)을 계산하고,
이를 기반으로 향후 모드별 최종 비용(`compute_final_cost`)으로 확장하기 위한 라이브러리다.

## 현재 지원 비용
1. 타겟과 각 셀 중심 사이의 거리
2. 각 셀 주변의 상태 전환 횟수 기반 안정성 비용
3. 로봇 위치와 각 셀 중심 사이의 거리 기반 접근 편의성 비용
4. 물체 배열(객체들이 일렬로 놓였다고 가정)에 수직하게 접근하도록 유도하는 접근각 비용

## cost_common
현재 `cost_common`은 위 네 비용을 각각 min-max 정규화한 뒤 가중 평균으로 결합한 값이다.
정규화는 candidate 셀만 대상으로 수행한다.

### 접근각 비용 (approach_angle)
각 후보 셀의 접근 방향 `target - cell` 이 `object_row_dir` 와 이루는 각을 본다.
원시값은 `|cos|`(0 = 수직 = 최적, 1 = 평행 = 최악)이며, 다른 항과 동일하게 정규화한다.
이 항은 `has_object_row_dir` 가 true 일 때만 의미를 가진다. 현재 **Mode3** 만 runner 에서
`object_row_dir`(로봇 정면에 고정된 측면축)을 설정하므로 이 항이 동작한다. **Mode1** 은
`object_row_dir` 를 설정하지 않아 이 항이 0(중립)으로 동작하고, 결과적으로 교집합 마스크 안의
가장 비용이 낮은 셀(가까움/안정)로 곧장 향한다.

## compute_final_cost
Mode1·Mode3 모두 `cost_common`을 그대로 최종 비용으로 사용한다. 두 모드의 차이는 runner 가
`object_row_dir`/`target_point`를 어떻게 정하느냐에만 있다(Mode1: 교집합 직진, Mode3: 정면 고정).
