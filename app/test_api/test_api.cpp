#include <petuum_ps_common/include/petuum_ps.hpp>
#include <petuum_ps_common/include/ps_table_group.hpp>
#include <thread>

class Test {
public:
  void Start() {
      petuum::PSTableGroup::RegisterThread();
      std::cout << "working" << std::endl;
      petuum::PSTableGroup::DeregisterThread();
  }
};

//int testmain() {
int main(int argc, char* argv[]) {
    petuum::PSTableGroup::RegisterRow<petuum::DenseRow<float> >(0);
    petuum::TableGroupConfig table_group_config;
    table_group_config.num_comm_channels_per_client = 4;
    table_group_config.num_total_clients = 1;
    table_group_config.num_tables = 1;
    table_group_config.num_local_app_threads = 5;
    table_group_config.client_id = 0;
    petuum::GetHostInfos("/root/mxnet/ps/app/test_api/bin/hostfile", &table_group_config.host_map);
    table_group_config.consistency_model = petuum::SSPPush;
    table_group_config.stats_path = "";
    petuum::PSTableGroup::Init(table_group_config, false);
    petuum::ClientTableConfig table_config;
    table_config.table_info.row_type = 0;
    table_config.table_info.table_staleness = 0;
    table_config.process_storage_type = petuum::BoundedDense;
    table_config.table_info.row_capacity = 9;
    table_config.process_cache_capacity = 3;
    table_config.table_info.row_oplog_type = petuum::RowOpLogType::kDenseRowOpLog;
    table_config.table_info.oplog_dense_serialized = true;
    table_config.table_info.dense_row_oplog_capacity = 9;
    table_config.table_info.server_table_logic = -1;
    table_config.thread_cache_capacity = 1;
    table_config.oplog_capacity = 3;
    table_config.process_storage_type = petuum::BoundedDense;
    table_config.oplog_type = petuum::Dense;
    petuum::PSTableGroup::CreateTable(0, table_config);
    petuum::PSTableGroup::CreateTableDone();
    Test test;
    std::vector<std::thread> threads(4);
    for (auto & thr: threads) {
        thr = std::thread(&Test::Start, std::ref(test));
    }
    for (auto & thr: threads) {
        thr.join();
    }
    petuum::PSTableGroup::ShutDown();
    return 0;
}

