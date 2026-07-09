from temporal_bridge import TemporalBridge

if __name__ == "__main__":
    timeline_index = TemporalBridge()

    # Log operational diagnostic entries mapped to timestamp tokens
    timeline_index.add_historical_record(epoch_time=1712214000, chunk_id=9001)
    timeline_index.add_historical_record(epoch_time=1712217600, chunk_id=9002)

    target_epoch = 1712217600
    matched_chunk = timeline_index.locate_epoch_match(target_epoch)

    print("=== TEMPORALBTREE-RAG CHRONO SCANNER ===")
    print(f"[*] Searched Epoch Boundary [{target_epoch}]. Target Result Chunk Extracted: {matched_chunk}")
