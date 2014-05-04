# Generic module

- "Existance-aware" [Object Pointers](#objectpointer)

## Object-Pointer

A simple smart pointer designed for manual memory managment. The most notable difference to "native" pointers is that a ObjectPointer is aware of the existance of the object it is pointing to.

```cpp
int* value = new int(666);
ObjectPointer<int> a = value;
ObjectPointer<int> b = value;
a.destroy();
// Both "a" and "b" are a nullptr now.
// Note that this behaviour only works if ObjectPointer::destroy is called
// Do not use 'delete' together with ObjectPointers
```

This can be used for referencing entities, for example in a AI subsystem, without the danger of running into invalid pointers.

```cpp
if(!mTarget) // Our target was destroyed (or never existed in the first place)
{
  mTarget = findNewTarget();
  if(mTarget) // Found a target, attack.
  {
    mState = AttackTarget;
    mTargetPosition = mTarget->pos(); // For anything else they just work like normal pointers. (Dereference with *, call methods with ->)
  }
}
```

### Exchanging resources at run-time

Aside from the *destroy* method object pointers also have a *replaceWith* method. Instead of setting all instances of that pointer to **nullptr** it sets them to the specified parameter.

Springbok uses ObjectPointers for all resources, in order to make hot swapping files possible.

```cpp
  Image img("test1.png");
  Image replacement("test2.png");
  img.TexturePtr.replaceWith(replacement.TexturePtr, true);
  // Delete the texture allocated for "test1.png" and replace it with "test2.png"
  // If 'false' is given instead of 'true' the reference will be replaced but the old texture never deleted
```