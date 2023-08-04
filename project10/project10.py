from ecdsa import SigningKey, SECP256k1, VerifyingKey
import time

def generate_keys():
    sk = SigningKey.generate(curve=SECP256k1)
    vk = sk.get_verifying_key()
    secret_key = sk.to_string().hex()
    verify_key = vk.to_string().hex()
    return secret_key,verify_key

#签名
def ecdsa_sign(secret_key, m):
    sk = SigningKey.from_string(bytes.fromhex(secret_key), curve=SECP256k1)
    signature = sk.sign(bytes(m, 'utf-8'))
    return signature.hex()

def Verify(verify_key, signature, m):
    vk = VerifyingKey.from_string(bytes.fromhex(verify_key), curve=SECP256k1)
    return vk.verify(bytes.fromhex(signature), bytes(m, 'utf-8'))

if __name__ == '__main__':
    sk, pk = generate_keys()
    m = 'message'
    ta=time.time()
    signature = ecdsa_sign(sk, m)
    tb=time.time()
    print('signature: ', signature)
    print('signature time: ',tb-ta,'s')
    tc=time.time()
    ver=Verify(pk, signature,m)
    td=time.time()
    print('verification result: ', ver)
    print('verification time: ',td-tc,'s')
