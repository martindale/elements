// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SCRIPT_SIGCACHE_H
#define BITCOIN_SCRIPT_SIGCACHE_H

#include "script/interpreter.h"

#include <secp256k1.h>
#include <secp256k1_rangeproof.h>
#include <vector>

// DoS prevention: limit cache size to less than 40MB (over 500000
// entries on 64-bit systems).
static const unsigned int DEFAULT_MAX_SIG_CACHE_SIZE = 40;

class CPubKey;

class CachingTransactionSignatureChecker : public TransactionSignatureChecker
{
private:
    bool store;

public:
    CachingTransactionSignatureChecker(const CTransaction* txToIn, unsigned int nInIn, const CTxOutValue& amount, const CTxOutValue& amountPreviousInput, const CScript& scriptFedRedeem, bool storeIn, PrecomputedTransactionData& txdataIn) : TransactionSignatureChecker(txToIn, nInIn, amount, amountPreviousInput, scriptFedRedeem), store(storeIn) {}

    bool VerifySignature(const std::vector<unsigned char>& vchSig, const CPubKey& vchPubKey, const uint256& sighash) const;
};

class CachingRangeProofChecker
{
private:
    bool store;
public:
    CachingRangeProofChecker(bool storeIn){
        store = storeIn;
    };

    bool VerifyRangeProof(const std::vector<unsigned char>& vchRangeProof, const std::vector<unsigned char>& vchCommitment, const std::vector<unsigned char>& vchAssetTag, const secp256k1_context* ctx) const;

};

#endif // BITCOIN_SCRIPT_SIGCACHE_H
